# Assignment 4 - OpenGL 3D Scene

## Overview

This project is a 3D scene rendered using OpenGL with GLFW and GLEW, implementing camera movement and object rendering using PLY models and BMP textures.
[![Demo Video]([https://img.youtube.com/vi/VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=VIDEO_ID](https://www.youtube.com/watch?v=qk8ixV8rSpk))
![Screenshot 1](Screenshots/Screenshot 1.png)
![Screenshot 2](Screenshots/Screenshot 2.png)
![Screenshot 3](Screenshots/Screenshot 3.png)
![Screenshot 4](Screenshots/Screenshot 4.png)

## Features

- 3D Scene Rendering with multiple textured objects
- Smooth Camera Movement using `WASD` and arrow keys
- Yaw (left/right rotation) with Arrow Keys and Pitch (up/down tilt) with `Q` / `E`
- Strafing Left/Right with `A` and `D`
- Dynamic Viewport Resizing
- Object Loading from .ply Files
- Texture Mapping using .bmp Files
- Depth Testing & Transparency Handling

## Controls

| Key     | Action |
|-----------|----------------|
| `W / ↑` | Move forward |
| `S / ↓` | Move backward |
| `A`     | Strafe left |
| `D`     | Strafe right|
| `←`     | Rotate Left (Yaw) |
| `→`     | Rotate Right (Yaw) |
| `Q`     | Look Up (Pitch) |
| `E`     | Look Down (Pitch) |
| `ESC`   | Quit Application |

## Installation & Compilation

### Dependencies

- OpenGL
- GLEW
- GLFW
- GLM
- SDL2

### Compiling the Project with CMake

1. Ensure all dependencies are installed (see `CMakesList.txt`).
2. Create a build directory and run CMake:
```bash
mkdir build && cd build
cmake ..
make
```
3. Run the executable:
```bash
./assignment4
```

### Manual Compilation (Without CMake)
```bash
# Compile all files
g++ -std=c++17 -c LoadBitmap.cpp $(pkg-config --cflags sdl2)
g++ -std=c++17 -c Camera.cpp -I/opt/homebrew/include
g++ -std=c++17 -c main.cpp -I/opt/homebrew/include
g++ -std=c++17 -c TexturedMesh.cpp -I/opt/homebrew/include
g++ -std=c++17 -o assignment4 main.o TexturedMesh.o LoadBitmap.o Camera.o $(pkg-config --cflags --libs sdl2) -I/opt/homebrew/include -L/opt/homebrew/lib -lGLEW -lglfw -framework OpenGL -framework Cocoa -framework IOKit
# Run the executable
./assignment4
```

## File Structure
```bash
📂 CS3388_Assignment4
├── 📄 main.cpp             # Main application loop
├── 📄 Camera.h             # Camera class for movement & rotation
├── 📄 TexturedMesh.h / TexturedMesh.cpp # Mesh & Texture Loading
├── 📄 LoadBitmap.cpp       # BMP texture loader
├── 📄 CMakeLists.txt       # CMake configuration for building the project
├── 📂 LinksHouse/          # PLY & BMP files for scene objects
├── 📄 README.md            # This file
```
## Troubleshooting

- If the window only shows a small portion of the scene, ensure `framebuffer_size_callback()` properly updates `glViewport()`.
- If arrow keys don’t rotate the camera, verify `yaw` is correctly updated inside `processInput()`.
- If models don't load, ensure `.ply` files are in the `LinksHouse/` directory.
- If textures don’t appear, check `.bmp` file paths and ensure OpenGL supports `GL_TEXTURE_2D`.
- If A / D keys don’t move left/right, verify `position -= speed * right;` is inside `processInput()`.
