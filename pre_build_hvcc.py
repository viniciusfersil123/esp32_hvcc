"""
Pre-build script for PlatformIO
Compiles Pure Data patch using hvcc before building the firmware
Generates controls code from board_config.json
"""
import os
import shutil
import subprocess
import sys
import json
import hashlib
from pathlib import Path

Import("env")


def _is_up_to_date(input_files, output_files):
    """Return True when all outputs exist and are newer than all inputs."""
    input_paths = [Path(p) for p in input_files if p]
    output_paths = [Path(p) for p in output_files if p]

    if not input_paths or not output_paths:
        return False

    if any(not p.exists() for p in output_paths):
        return False

    latest_input = max(p.stat().st_mtime for p in input_paths if p.exists())
    oldest_output = min(p.stat().st_mtime for p in output_paths)
    return oldest_output >= latest_input


def _collect_hvcc_outputs(output_dir):
    """Collect generated hvcc source/header files."""
    c_dir = output_dir / 'c'
    if not c_dir.exists():
        return []
    return [p for p in c_dir.rglob('*') if p.is_file() and p.suffix in {'.c', '.cpp', '.h', '.hpp'}]


def _compute_file_sha256(path):
    """Compute SHA256 for a file."""
    h = hashlib.sha256()
    with open(path, 'rb') as f:
        while True:
            chunk = f.read(65536)
            if not chunk:
                break
            h.update(chunk)
    return h.hexdigest()


def _load_hvcc_state(state_file):
    """Load persisted hvcc state."""
    try:
        if state_file.exists():
            with open(state_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                if isinstance(data, dict):
                    return data
    except Exception:
        pass
    return {}


def _save_hvcc_state(state_file, state):
    """Persist hvcc state atomically."""
    state_file.parent.mkdir(parents=True, exist_ok=True)
    tmp_file = state_file.with_suffix('.tmp')
    with open(tmp_file, 'w', encoding='utf-8') as f:
        json.dump(state, f, indent=2, sort_keys=True)
    tmp_file.replace(state_file)


def _hvcc_output_needs_regeneration(project_dir, pd_patch, output_dir):
    """Determine whether hvcc output should be regenerated."""
    if os.environ.get('HVCC_FORCE_REBUILD', '').strip() in {'1', 'true', 'TRUE', 'yes', 'YES'}:
        print("HVCC_FORCE_REBUILD set - forcing hvcc regeneration")
        return True

    c_dir = output_dir / 'c'
    required_files = [
        c_dir / 'Heavy_heavy.cpp',
        c_dir / 'Heavy_heavy.h',
        c_dir / 'HeavyContext.cpp',
        c_dir / 'HeavyContext.hpp',
        c_dir / 'HvHeavy.cpp',
        c_dir / 'HvHeavy.h',
    ]

    if any(not p.exists() for p in required_files):
        missing = [str(p.relative_to(project_dir)) for p in required_files if not p.exists()]
        print("HVCC output missing files:")
        for m in missing:
            print(f"  - {m}")
        return True

    hvcc_outputs = _collect_hvcc_outputs(output_dir)
    if not hvcc_outputs:
        print("HVCC output folder exists but no generated files were found")
        return True

    # Use a content-based state first (more reliable than mtimes).
    state_file = project_dir / '.pio' / 'hvcc_state.json'
    current_pd_hash = _compute_file_sha256(pd_patch)
    state = _load_hvcc_state(state_file)
    if state.get('main_pd_sha256') == current_pd_hash:
        return False
    if state.get('main_pd_sha256'):
        print("Pure Data patch content changed and HVCC will be regenerated")
        return True

    # Fallback for first run / missing state file.
    input_files = [pd_patch]
    if not _is_up_to_date(input_files, hvcc_outputs):
        print("HVCC output is older than inputs and will be regenerated")
        return True

    return False

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

    template_h = project_dir / 'controls_generated.h.jinja2'
    template_c = project_dir / 'controls_generated.c.jinja2'
    generator_script = project_dir / 'generate_controls.py'

    output_h = project_dir / 'src' / 'controls_generated.h'
    output_c = project_dir / 'src' / 'controls_generated.c'

    if _is_up_to_date(
        [config_file, template_h, template_c, generator_script],
        [output_h, output_c]
    ):
        print("✓ Controls code already up to date")
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

    embed_script = project_dir / 'generate_board_config_embed.py'
    config_file = project_dir / 'board_config.json'
    embedded_output = project_dir / 'src' / 'board_config_embedded.c'

    if _is_up_to_date([config_file, embed_script], [embedded_output]):
        print("✓ Embedded board config already up to date")
        return
    
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
    build_dir = Path(env.subst('$BUILD_DIR'))
    
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
    
    needs_hvcc = _hvcc_output_needs_regeneration(project_dir, pd_patch, output_dir)

    if needs_hvcc:
        # Keep output directory to preserve file mtimes for unchanged files.
        output_dir.mkdir(parents=True, exist_ok=True)

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
            print("PRE-BUILD: Complete - HVCC code regenerated")
            print("=" * 60)
            print("")

            # Persist state so unchanged patches skip regeneration next build.
            state_file = project_dir / '.pio' / 'hvcc_state.json'
            _save_hvcc_state(state_file, {
                'main_pd_sha256': _compute_file_sha256(pd_patch)
            })

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
    else:
        print("✓ HVCC output is up to date - skipping hvcc regeneration")

    # Always check generated support files incrementally.
    print("")
    generate_controls_code(project_dir)

    print("")
    generate_board_config_embed(project_dir)

    print("=" * 60)
    print("PRE-BUILD: Complete")
    print("=" * 60)
    print("")

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

