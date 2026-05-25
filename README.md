# Pong Classic - Raylib Game

Classic Pong game built with C++ and Raylib library. Features main menu, pause menu, and smooth gameplay.

## Features

- **Main Menu** - Start game or quit with keyboard navigation
- **Pause Menu** - Resume, restart, or quit to menu
- **Classic Pong Gameplay** - Player vs CPU
- **Smooth Controls** - Keyboard-based paddle movement
- **Score Tracking** - Real-time score display
- **Game State Management** - MENU, PLAYING, PAUSED states

## Requirements

- **Windows 10/11**
- **w64devkit** (MinGW-w64 compiler)
- **raylib** library (tested with version 6.0)

## Installation

### 1. Install w64devkit (Compiler)

1. Download w64devkit from https://github.com/skeeto/w64devkit/releases
2. Extract to `D:\Installer\w64devkit` (or your preferred location)
3. Add `D:\Installer\w64devkit\bin` to your system PATH (optional but recommended)

### 2. Install raylib

1. Download raylib from https://github.com/raysan5/raylib/releases
2. Extract to `C:\raylib` (or your preferred location)
3. Ensure raylib.h and libraylib.a are accessible

### 3. Configure Makefile

Update the Makefile with your paths:

```makefile
COMPILER_PATH      ?= D:/Installer/w64devkit/bin
RAYLIB_PATH        ?= C:/raylib/raylib
```

## How to Compile

### Using Makefile (Recommended)

```bash
D:\Installer\w64devkit\bin\mingw32-make
```

This will compile the project and create `game.exe`.

### Using g++ Directly

```bash
D:\Installer\w64devkit\bin\g++ main.cpp -o game.exe -I"C:/raylib/raylib/src" -L"C:/raylib/raylib/src" -lraylib -lopengl32 -lgdi32 -lwinmm -std=c++14
```

## How to Run

```bash
./game.exe
```

Or simply double-click `game.exe` in File Explorer.

## Game Controls

### Main Menu
- **UP/DOWN Arrows** - Navigate menu options
- **ENTER** - Select option
- **Options**: START GAME, QUIT

### Gameplay
- **Player (Right Paddle)**: UP/DOWN Arrow keys
- **CPU (Left Paddle)**: AI-controlled (automatic)
- **Pause**: Press `P` key during gameplay
- **Exit Game**: ESC or close window

### Pause Menu
- **UP/DOWN Arrows** - Navigate menu options
- **ENTER** - Select option
- **RESUME** - Continue playing
- **RESTART** - Reset score and ball position
- **QUIT TO MENU** - Return to main menu

## Project Structure

```
pong-classic/
├── main.cpp           # Main game source code (with menu system)
├── Makefile           # Build configuration
├── README.md          # This file
├── LICENSE.txt        # MIT License
├── game.exe           # Compiled executable (after build)
├── libgcc_s_dw2-1.dll # GCC runtime library
├── libstdc++-6.dll    # C++ standard library
├── main.code-workspace # VS Code workspace configuration
└── preview.jpg        # Game preview image
```

## Current Configuration

- **Compiler**: w64devkit at `D:/Installer/w64devkit/bin`
- **Raylib**: Installed at `C:/raylib/raylib`
- **Raylib Version**: 6.0
- **C++ Standard**: C++14
- **Executable**: `game.exe`

## Troubleshooting

### "raylib.h: No such file or directory"
- Ensure raylib is installed and the path in Makefile is correct
- Check that raylib.h exists in `C:/raylib/raylib/src`
- Verify RAYLIB_PATH points to correct location (e.g., `C:/raylib/raylib`)

### "g++: command not found"
- Ensure w64devkit is installed and the path is correct
- Try using the full path: `D:\Installer\w64devkit\bin\g++`
- Verify COMPILER_PATH in Makefile is correct

### "cannot find -lraylib"
- Ensure raylib library file (libraylib.a) is in the lib directory
- Check that RAYLIB_PATH in Makefile points to the correct location
- Verify library path includes `C:/raylib/raylib/src`

### Pause key not working
- Ensure you're running `game.exe` (not old `main.exe`)
- Press `T` key during gameplay to pause
- Verify the code was recompiled after key changes

## Development Notes

### Game States
The game uses a state machine with three states:
- **MENU**: Main menu with start/quit options
- **PLAYING**: Active gameplay with paddle and ball updates
- **PAUSED**: Pause menu with resume/restart/quit options

### Key Features Implemented
- Main menu with keyboard navigation
- Pause menu with game state management
- Score tracking and display
- Ball collision detection and reset
- Paddle movement with boundary limits
- Visual feedback for menu selection

## License

This project is licensed under the MIT License - see LICENSE.txt for details.

## Credits

- Built with [Raylib](https://www.raylib.com/)
- Based on Raylib C++ Starter Template by Nick Koumaris
- Enhanced with menu system and improved controls

