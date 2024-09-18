# 3D Cube Renderer

## Overview

This project demonstrates a 3D cube rendering application developed using C++ and SDL2. The application renders a 3D cube and performs real-time rotation. Users can control the cube using the WASD keys or arrow keys.

https://github.com/user-attachments/assets/fd2e0713-612d-4f67-868f-6fc2f1eaa7b3

## Features

- **3D Cube Rendering**: Renders a 3D cube on a 2D screen.
- **Automatic Rotation**: The cube rotates automatically without user input.
- **User Controls**: Control the cube's rotation using WASD keys or arrow keys.
- **Efficient Rendering**: Utilizes efficient pixel manipulation and line drawing algorithms.
- **Real-Time Performance**: Optimized for smooth animation on a 640x480 resolution window.

## Files

- `main.cpp`: The main source file containing the cube rendering logic.
- `screen.h`: Header file with definitions and declarations for screen handling.
- `SDL2.dll`: The SDL2 dynamic library required for running the application.
- `main.exe`: The executable file for running the 3D Cube Renderer application.
- `screen.exe`: Another executable related to screen handling.
- `pixel.exe`: An executable related to pixel operations.

## Build Instructions

To build and run the 3D Cube Renderer project, follow these steps:

1. **Install SDL2**

2. **Compile the Code**:
   ```bash
   g++ main.cpp -I/path/to/SDL2/include -L/path/to/SDL2/lib -lSDL2 -o main.exe
