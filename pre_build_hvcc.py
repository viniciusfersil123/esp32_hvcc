"""
Pre-build script for PlatformIO
Compiles Pure Data patch using hvcc before building the firmware
Generates controls code from board_config.json
"""
import os
import shutil
import subprocess
import sys
from pathlib import Path

Import("env")

def fix_esp32_compatibility(output_dir):
    """Fix ESP32-specific compatibility issues in generated code"""
    
    # Fix HvMessage.c format specifiers for uint32_t
    hvmessage_file = output_dir / 'c' / 'HvMessage.c'
    
    if hvmessage_file.exists():
        print("Applying ESP32 compatibility patches to HvMessage.c")
        
        content = hvmessage_file.read_text()
        
        # Fix format specifiers: %X -> %lX for uint32_t on ESP32
        content = content.replace('"0x%X"', '"0x%lX"')
        
        hvmessage_file.write_text(content)
        print("✓ Applied format specifier fix (uint32_t)")
    else:
        print(f"WARNING: {hvmessage_file} not found for patching")

def generate_controls_code(project_dir):
    """Generate controls code from board_config.json"""
    
    print("Generating controls code from board_config.json...")
    
    config_file = project_dir / 'board_config.json'
    if not config_file.exists():
        print(f"WARNING: {config_file} not found - skipping controls generation")
        return
    
    # Run the code generator
    try:
        import sys
        sys.path.insert(0, str(project_dir))
        
        # Import and run the generator
        spec = __import__('importlib.util').util.spec_from_file_location(
            "generate_controls", str(project_dir / 'generate_controls.py')
        )
        generator = __import__('importlib.util').util.module_from_spec(spec)
        spec.loader.exec_module(generator)
        
        success = generator.generate_controls_code(str(config_file), str(project_dir / 'src'))
        
        if success:
            print("✓ Controls code generated successfully")
        else:
            print("ERROR: Controls code generation failed")
            
    except Exception as e:
        print(f"WARNING: Controls generation failed: {e}")

def generate_board_config_embed(project_dir):
    """Generate embedded board_config.json as C code"""
    
    print("Generating embedded board_config.json...")
    
    # Run the board config embedder
    try:
        result = subprocess.run(
            ['python3', str(project_dir / 'generate_board_config_embed.py')],
            cwd=str(project_dir),
            capture_output=True,
            text=True,
            check=True
        )
        print("✓ Board config embedded successfully")
    except subprocess.CalledProcessError as e:
        print(f"WARNING: Failed to embed board config: {e}")
        if e.stderr:
            print(e.stderr)

            
    except ImportError as e:
        print(f"WARNING: Could not import jinja2: {e}")
        print("Install with: pip3 install jinja2")
    except Exception as e:
        print(f"ERROR: Failed to generate controls code: {e}")
        import traceback
        traceback.print_exc()

def compile_pd_patch(*args, **kwargs):
    """Compile Pure Data patch with hvcc"""
    
    print("")
    print("=" * 60)
    print("PRE-BUILD: HVCC Pure Data Compilation")
    print("=" * 60)
    
    # Paths
    project_dir = Path(env.get('PROJECT_DIR', os.getcwd()))
    src_dir = project_dir / 'src'
    pd_patch = src_dir / 'main.pd'
    output_dir = src_dir / 'output'
    build_dir = Path(env.get('BUILD_DIR', project_dir / '.pio' / 'build' / 'esp32dev'))
    
    print(f"Project dir: {project_dir}")
    print(f"Source dir: {src_dir}")
    print(f"PD patch: {pd_patch}")
    print(f"Output dir: {output_dir}")
    print(f"Build dir: {build_dir}")
    
    # Check if patch exists
    if not pd_patch.exists():
        print(f"WARNING: Pure Data patch not found: {pd_patch}")
        print("Skipping hvcc compilation - will use existing output if available")
        if not output_dir.exists():
            print("ERROR: No output directory found and no patch to compile!")
            print("Please create main.pd or run hvcc manually")
            sys.exit(1)
        return
    
    # Remove old output directory
    if output_dir.exists():
        print(f"Removing old output: {output_dir}")
        try:
            shutil.rmtree(output_dir)
        except Exception as e:
            print(f"WARNING: Could not remove old output: {e}")
    
    # Clean old object files to force recompilation
    print("Cleaning old object files to force rebuild...")
    output_obj_dir = build_dir / 'src' / 'output'
    if output_obj_dir.exists():
        try:
            shutil.rmtree(output_obj_dir)
            print(f"✓ Removed old object files from {output_obj_dir}")
        except Exception as e:
            print(f"WARNING: Could not remove object files: {e}")
    
    # Run hvcc
    try:
        print(f"Running: hvcc {pd_patch} -o {output_dir}")
        
        result = subprocess.run(
            ['hvcc', str(pd_patch), '-o', str(output_dir)],
            cwd=str(src_dir),
            capture_output=True,
            text=True,
            check=True
        )
        
        if result.stdout:
            print("HVCC output:")
            print(result.stdout)
        
        if result.stderr:
            print("HVCC stderr:")
            print(result.stderr)
        
        print("✓ HVCC compilation successful")
        
        # Post-process generated code for ESP32 compatibility
        print("Applying ESP32 patches...")
        fix_esp32_compatibility(output_dir)
        
        print("=" * 60)
        print("PRE-BUILD: Complete - all HVCC files will be recompiled")
        print("=" * 60)
        print("")
        
        # Generate controls code after HVCC compilation
        print("")
        generate_controls_code(project_dir)
        
        # Generate embedded board config
        print("")
        generate_board_config_embed(project_dir)
        
    except subprocess.CalledProcessError as e:
        print("=" * 60)
        print("ERROR: hvcc compilation failed")
        print("=" * 60)
        print(f"Return code: {e.returncode}")
        if e.stdout:
            print("STDOUT:", e.stdout)
        if e.stderr:
            print("STDERR:", e.stderr)
        sys.exit(1)
        
    except FileNotFoundError:
        print("=" * 60)
        print("ERROR: hvcc not found in PATH")
        print("=" * 60)
        print("Please install hvcc:")
        print("  pip3 install hvcc")
        print("Or ensure it's in your PATH")
        sys.exit(1)
    
    except Exception as e:
        print("=" * 60)
        print(f"ERROR: Unexpected error: {e}")
        print("=" * 60)
        import traceback
        traceback.print_exc()
        sys.exit(1)

# Run generation immediately when the extra script is loaded.
# This guarantees generated headers/sources exist before compile starts,
# regardless of framework-specific build target naming.
compile_pd_patch()

# Add main.pd as a dependency so changes trigger rebuild
project_dir = Path(env.get('PROJECT_DIR', os.getcwd()))
pd_patch = project_dir / 'src' / 'main.pd'
if pd_patch.exists():
    env.Depends("$BUILD_DIR/${PROGNAME}.elf", str(pd_patch))
    print(f"✓ Registered {pd_patch.name} as build dependency")

