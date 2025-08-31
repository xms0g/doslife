# doslife: Conway's Game of Life in 16-bit Real Mode 
Conway's Game of Life is a zero-player game that simulates cellular automaton behavior, meaning that its evolution is determined by its initial state, requiring no further input from the player. This implementation displays the game in real-time on a DOS terminal using VGA mode 13h graphics. Each character on the screen represents a cell, either alive or dead, that evolves based on its neighbors.
You can download the `EXE` file from [itch.io](https://ms0g.itch.io/doslife).

<img src="ASSETS/doslife.gif" alt="image" width="700" height="auto">

## Rules
+ A live cell that has live neighbors below 2 or above 3 dies.
+ A dead cell that has 3 live neighbors becomes a live cell.

## Prerequisites
- **Turbo C++** (`TCC.EXE`) version 3.0 or later  
- **Turbo Assembler** (`TASM.EXE`) version 4.1 or later  
- **Turbo Linker** (`TLINK.EXE`) version 5.0 or later  
- **DOSBox** emulator or a real MS-DOS-compatible computer

## Building
```bash
C:\>MAKE.EXE
```
## Run
```bash
C:\>DOSLIFE.EXE
```
## License
This project is licensed under the GPL-2.0 License. See the LICENSE file for details.

