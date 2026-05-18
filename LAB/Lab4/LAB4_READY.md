# LAB4 Ready Notes

## What This Project Does

- Scans the 4x4 keypad in assembly.
- Uses PC0-PC3 as row outputs.
- Uses PB1, PB2, PB3, and PB5 as column inputs.
- Sends the detected key character to Tera Term through USART2.
- Uses software debouncing by verifying a stable press and then waiting for release.
- Uses open-drain row outputs so multi-key presses do not short a high row directly into a low row.

## Keil Project Location

- Project root: `D:\Keil\lab4`
- Project file: `D:\Keil\lab4\lab.uvprojx`
- Main assembly file: `D:\Keil\lab4\main.s`
- Generated image: `D:\Keil\lab4\Objects\lab.axf`
- Generated hex: `D:\Keil\lab4\Objects\lab.hex`

## Keypad Wiring

- R1 -> PC0
- R2 -> PC1
- R3 -> PC2
- R4 -> PC3
- C1 -> PB1
- C2 -> PB2
- C3 -> PB3
- C4 -> PB5

Key order on the keypad:

```text
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```

Important hardware note:

- Add external 2.2k pull-up resistors from PB1, PB2, PB3, and PB5 to 3.3V on the breadboard.
- The lab sheet explicitly says the internal pull-ups are too weak for this setup.

## Pre-Lab Register Answers

### GPIOC MODER

- Configure PC0-PC3 as digital outputs.
- Mask: `0x000000FF`
- Value: `0x00000055`

### GPIOB MODER

- Configure PB1, PB2, PB3, and PB5 as digital inputs.
- Mask: `0x00000CFC`
- Value: `0x00000000`

### GPIOC ODR Values

- Pull down all rows: `0x00000000`
- Pull down row 1 only: `0x0000000E`
- Pull down row 2 only: `0x0000000D`
- Pull down row 3 only: `0x0000000B`
- Pull down row 4 only: `0x00000007`

These row-only values assume open-drain outputs:

- `0` means the selected row is actively pulled low.
- `1` means the other rows are released, not actively driven high.

### GPIOB IDR Masks

- Column 1 mask (PB1): `0x00000002`
- Column 2 mask (PB2): `0x00000004`
- Column 3 mask (PB3): `0x00000008`
- Column 4 mask (PB5): `0x00000020`

## Post-Lab Answer Draft

### 1. How is software debouncing implemented?

The program first detects a candidate key, waits for a debounce delay, and scans again to confirm that the same key is still present. After that, it waits until all keys are released, delays again, and confirms the release before printing the character. This prevents a bouncing key from being reported multiple times.

### 2. What does it mean that the internal pull-up resistors are too weak?

The STM32L4 internal pull-ups are much larger resistance values, roughly tens of kilo-ohms, so they can only source a small current. In this keypad circuit the column lines also see capacitance and switching transients, so the weak internal pull-ups do not restore the line to a clean logic high quickly or strongly enough. The external 2.2k pull-ups provide a much stronger and more stable high level.

### 3. How to avoid the multi-key short-circuit case?

Do not drive the inactive row outputs high in push-pull mode. Instead, configure the row pins as open-drain outputs and only pull the active row low. The inactive rows are written as `1`, which leaves them high-impedance rather than sourcing current. That removes the direct high-to-low short path through simultaneously pressed keys.

### 4. Can the algorithm detect all keys in the two cases?

Case 1:

- Yes, in principle.
- Reason: both keys are in the same column but different rows.
- To detect all of them, the flowchart must not stop after the first detected key.
- For each selected row, test all four columns and record every low column.
- Continue scanning the remaining rows before reporting the final set of keys.

Case 2:

- No, not reliably.
- Reason: this is the classic ghosting case for a matrix keypad without isolation diodes.
- Three pressed keys can create an electrical path that makes the fourth corner appear pressed even when it is not.
- Software alone cannot uniquely distinguish the real 3-key pattern from the ghosted 4-key pattern in a plain matrix.

## In-Lab Checklist

1. Wire the keypad exactly as listed above.
2. Add four external 2.2k pull-up resistors from PB1/PB2/PB3/PB5 to 3.3V.
3. Open `D:\Keil\lab4\lab.uvprojx` in Keil.
4. Confirm the project still builds.
5. Flash the board.
6. Open Tera Term on the correct serial port.
7. Press keypad buttons and confirm the corresponding character appears in Tera Term.
8. Take a photo of the real circuit for submission.
9. Fill the participation/contribution table in the lab report.

## Build Status

- Batch build completed successfully in Keil.
- Result: `0 Error(s), 1 Warning(s)`
- Warning: `L6314W: No section matches pattern *(InRoot$$Sections).`
- This warning is from the scatter file/template setup and does not block the build.
