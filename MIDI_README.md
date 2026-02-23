# MIDI Implementation for ESP32 HVCC

This implementation provides full MIDI protocol support for Pure Data patches compiled with HVCC running on ESP32, similar to how libdaisy and pd2dsy handle MIDI on Daisy hardware.

## Features

### MIDI Input (to Pure Data)
- **[notein]** - Note On/Off messages with velocity
- **[ctlin]** - Control Change messages
- **[pgmin]** - Program Change messages
- **[touchin]** - Channel Aftertouch messages
- **[bendin]** - Pitch Bend messages
- **[midiin]** - Raw MIDI bytes
- **[midirealtimein]** - MIDI Realtime messages (clock, start, stop, etc.)

### MIDI Output (from Pure Data)
- **[noteout]** - Send Note On/Off with velocity
- **[ctlout]** - Send Control Change
- **[pgmout]** - Send Program Change
- **[touchout]** - Send Channel Aftertouch
- **[bendout]** - Send Pitch Bend
- **[polytouchout]** - Send Polyphonic Aftertouch
- **[midiout]** - Send raw MIDI bytes

## Hardware Configuration

### UART MIDI (Default)
MIDI is typically implemented over UART at 31250 baud. Configure pins in `board_config.json`:

```json
{
  "midi": {
    "transport": "uart",
    "uart_tx_pin": 17,
    "uart_rx_pin": 16,
    "enable_input": true,
    "enable_output": true
  }
}
```

**Hardware Requirements:**
- MIDI IN: Connect optocoupler circuit to RX pin (16)
- MIDI OUT: Connect to TX pin (17) through current-limiting resistor (220Ω)
- Standard MIDI 5-pin DIN connectors

### USB MIDI
USB MIDI support is planned but not yet implemented. It will use TinyUSB for USB device communication.

## Pure Data Usage Examples

### Basic MIDI Input
```
[notein]
|    |  |
|    |  [channel]
|    [velocity]
[note]
```

### MIDI Output
```
[60(     [100(    [1(
|        |        |
[noteout]
```

### Control Change
```
[ctlin 1]  <- Listen to CC#1 (Mod Wheel)
|    |  |
|    |  [channel]
|    [controller]
[value]
```

### Pitch Bend
```
[bendin]
|     |
|     [channel]
[0-16383]  <- 8192 is center
```

## Implementation Details

### Message Parsing
- Uses running status for efficient parsing
- Handles realtime messages that can interrupt data flow
- Processes messages in real-time on the main audio thread
- FIFO buffer for outgoing messages to prevent blocking

### Integration Points

**main.c:**
- `heavy_send_hook()` - Routes Heavy output messages to MIDI
- `midi_process()` - Called in audio loop to handle I/O
- `load_midi_config()` - Parses board_config.json

**midi_handler.c:**
- `midi_init()` - Initialize UART/USB transport
- `midi_process()` - Poll for input, flush output FIFO
- `midi_handle_heavy_send()` - Convert Heavy messages to MIDI
- `midi_process_input_byte()` - Parse incoming MIDI bytes

### Heavy Receiver Hashes
The implementation uses pre-computed hashes for fast message routing:
- `HV_HASH_NOTEIN` (0x67E37CA3)
- `HV_HASH_CTLIN` (0x41BE0F9C)
- `HV_HASH_PGMIN` (0x2E1EA03D)
- etc.

These match the standard Heavy/HVCC receiver names.

## Performance Considerations

- MIDI processing runs on the audio thread for minimal latency
- FIFO buffer prevents audio glitches from MIDI output
- Running status reduces UART bandwidth usage
- Non-blocking I/O prevents audio dropouts

## Differences from libdaisy

1. **No DaisySP dependency** - Pure ESP-IDF implementation
2. **JSON configuration** - Uses board_config.json instead of C++ config
3. **UART focus** - Hardware serial MIDI is primary transport
4. **Simplified** - No CV input mapping (can be added if needed)

## Testing

### Loopback Test
Connect MIDI OUT to MIDI IN (with proper optocoupler):

```
[metro 1000]
|
[60(
|
[noteout]

[notein]
|  |  |
[pack f f f]
|
[print MIDI_ECHO]
```

Should print received notes every second.

### External Devices
- Connect MIDI keyboard to MIDI IN
- Connect to synthesizer/DAW via MIDI OUT
- Use MIDI monitor software to verify output

## Troubleshooting

**No MIDI input:**
- Check RX pin and optocoupler circuit
- Verify baud rate (31250)
- Check `enable_input: true` in config
- Look for "MIDI handler ready" in logs

**No MIDI output:**
- Check TX pin wiring
- Verify `enable_output: true` in config
- Check FIFO full warnings in logs
- Test with MIDI monitor

**Latency issues:**
- MIDI processing runs every audio block
- Reduce audio block size for lower latency
- Check for FIFO overflow messages

## Future Enhancements

- [ ] USB MIDI device support (TinyUSB)
- [ ] USB MIDI host support (for controllers)
- [ ] SysEx message handling
- [ ] MIDI clock sync
- [ ] MPE (MIDI Polyphonic Expression)
- [ ] Multiple MIDI ports
- [ ] MIDI learn functionality

## References

- [MIDI 1.0 Specification](https://www.midi.org/specifications)
- [libdaisy MIDI](https://github.com/electro-smith/libDaisy)
- [pd2dsy](https://github.com/electro-smith/pd2dsy)
- [Heavy/HVCC Documentation](https://github.com/Wasted-Audio/hvcc)
