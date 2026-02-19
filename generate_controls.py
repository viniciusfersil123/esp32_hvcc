"""
Code generator for ESP32 HVCC controls
Generates C code from board_config.json using Jinja2 templates
"""
import json
import sys
from pathlib import Path
from jinja2 import Environment, FileSystemLoader, select_autoescape

# ESP32 GPIO to ADC mapping
# Maps GPIO pin numbers to (ADC_UNIT, ADC_CHANNEL)
ESP32_ADC_MAPPING = {
    # ADC1 channels
    32: (1, 4),   # ADC1_CH4
    33: (1, 5),   # ADC1_CH5
    34: (1, 6),   # ADC1_CH6
    35: (1, 7),   # ADC1_CH7
    36: (1, 0),   # ADC1_CH0
    37: (1, 1),   # ADC1_CH1
    38: (1, 2),   # ADC1_CH2
    39: (1, 3),   # ADC1_CH3
    # ADC2 channels (can only be used when WiFi is off)
    4: (2, 0),    # ADC2_CH0
    0: (2, 1),    # ADC2_CH1
    2: (2, 2),    # ADC2_CH2
    15: (2, 3),   # ADC2_CH3
    13: (2, 4),   # ADC2_CH4
    12: (2, 5),   # ADC2_CH5
    14: (2, 6),   # ADC2_CH6
    27: (2, 7),   # ADC2_CH7
}

def get_adc_info(pin):
    """Get ADC unit and channel for a GPIO pin"""
    if pin not in ESP32_ADC_MAPPING:
        raise ValueError(f"GPIO{pin} is not an ADC pin on ESP32")
    adc_unit, adc_channel = ESP32_ADC_MAPPING[pin]
    return adc_unit, adc_channel

def process_adc_config(adc_config):
    """Process ADC config and add ADC unit/channel if not present"""
    pin = adc_config.get('pin')
    if not pin:
        raise ValueError("ADC config must have a 'pin' field")
    
    # Auto-detect ADC unit and channel if not specified
    if 'adc_unit' not in adc_config or 'adc_channel' not in adc_config:
        adc_unit, adc_channel = get_adc_info(pin)
        adc_config['adc_unit'] = adc_unit
        adc_config['adc_channel'] = adc_channel
    
    # Create a sanitized name for C defines (replace spaces with underscores, uppercase)
    adc_config['define_name'] = adc_config['name'].replace(' ', '_').upper()
    
    return adc_config

def generate_controls_code(config_path, output_dir=None):
    """
    Generate controls code from board_config.json
    
    Args:
        config_path: Path to board_config.json
        output_dir: Output directory (default: same as config)
    """
    config_path = Path(config_path)
    output_dir = Path(output_dir or config_path.parent)
    
    print(f"Loading configuration from: {config_path}")
    
    # Load configuration
    try:
        with open(config_path) as f:
            config = json.load(f)
    except Exception as e:
        print(f"ERROR: Failed to load configuration: {e}")
        return False
    
    # Extract controls configuration
    controls = config.get('controls', {})
    adcs = controls.get('adcs', [])
    buttons = controls.get('buttons', [])
    
    # Process ADC configs to add ADC unit/channel
    try:
        processed_adcs = []
        for adc in adcs:
            processed = process_adc_config(adc.copy())
            processed_adcs.append(processed)
            print(f"  {processed['name']:20} (GPIO{processed['pin']:2d}) -> {processed['receiver']:15} [{processed['define_name']}]")
        adcs = processed_adcs
    except ValueError as e:
        print(f"ERROR: {e}")
        return False
    
    print(f"Processing {len(adcs)} ADC control(s) and {len(buttons)} button(s)")
    
    # Setup Jinja2 environment
    env = Environment(
        loader=FileSystemLoader(config_path.parent),
        autoescape=select_autoescape(['h', 'c'])
    )
    
    # Render header file
    try:
        template_h = env.get_template('controls_generated.h.jinja2')
        header_code = template_h.render(adcs=adcs, buttons=buttons)
        
        header_path = output_dir / 'controls_generated.h'
        with open(header_path, 'w') as f:
            f.write(header_code)
        print(f"✓ Generated: {header_path}")
    except Exception as e:
        print(f"ERROR: Failed to generate header: {e}")
        return False
    
    # Render implementation file
    try:
        template_c = env.get_template('controls_generated.c.jinja2')
        impl_code = template_c.render(adcs=adcs, buttons=buttons)
        
        impl_path = output_dir / 'controls_generated.c'
        with open(impl_path, 'w') as f:
            f.write(impl_code)
        print(f"✓ Generated: {impl_path}")
    except Exception as e:
        print(f"ERROR: Failed to generate implementation: {e}")
        return False
    
    print("✓ Controls code generation successful")
    return True

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python generate_controls.py <config.json> [output_dir]")
        sys.exit(1)
    
    config_path = sys.argv[1]
    output_dir = sys.argv[2] if len(sys.argv) > 2 else None
    
    success = generate_controls_code(config_path, output_dir)
    sys.exit(0 if success else 1)

