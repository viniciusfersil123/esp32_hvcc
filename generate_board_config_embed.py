#!/usr/bin/env python3
"""
Generate embedded board_config data as C code
"""

import json

def main():
    # Read board_config.json
    with open('board_config.json', 'r') as f:
        config = json.load(f)
    
    # Convert to compact JSON string
    json_str = json.dumps(config, separators=(',', ':'))
    
    # Escape quotes and backslashes for C string
    c_str = json_str.replace('\\', '\\\\').replace('"', '\\"')
    
    # Generate C source file
    with open('src/board_config_embedded.c', 'w') as f:
        f.write('// Auto-generated from board_config.json - DO NOT EDIT\n\n')
        f.write('const char board_config_json_start[] = \n')
        f.write(f'"{c_str}";\n\n')
        f.write('const char board_config_json_end[] = "";\n')

if __name__ == '__main__':
    main()
