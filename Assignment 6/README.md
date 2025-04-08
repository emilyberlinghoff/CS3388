# Assignment 6 - Water Rendering with Textured Models in OpenGL

## Overview

This project implements animated water rendering using tessellation and geometry shaders in OpenGL. It integrates multiple textured 3D models (.ply format) including a boat, head, and eyes, alongside Gerstner wave simulation for realistic surface movement. Additional features include interactive camera controls, shader-driven lighting, and dynamic mesh loading with UV-mapped textures.

## Key Functionalities

### Textured Model Rendering

- **PLY Parsing**: Each model is loaded from a `.ply` file including positions, normals, and UVs.
- **Texture Mapping**: Corresponding BMP textures are applied via fragment shader sampling.
- **Mesh Buffering**: Vertex, normal, UV, and index buffers are managed per mesh and rendered using VAOs and VBOs.

### Water Shader Implementation
- **Tessellation and Geometry Shaders**: Used to animate a water surface mesh with Gerstner waves.
- **Displacement Mapping**: A grayscale texture (`displacement-map1.bmp`) is used to modulate water height.
- **Realistic Surface Motion**: Vertex positions are dynamically updated with sinusoidal wave calculations in shaders.

### Camera Controls

- **Click and Dra**g**: Rotates the camera using spherical coordinates (θ, ϕ).
- **Arrow Keys**: Up/down arrows move the camera forward/backward along the radial vector.
- **Initial View**: Starts with the camera looking at the water surface and scene objects.

### Shader Loading System

A generalized `LoadShaders` function accepts up to five shader types: vertex, fragment, tessellation control, tessellation evaluation, and geometry. Unused paths are passed as empty strings.

### Controls

Didn't have time to implement.

## Compilation and Running

To build and run the application:

```bash
make clean && make
./water
```

## Output Screenshots

![Output](https://github.com/emilyberlinghoff/CS3388/blob/main/Assignment%206/output.png)

## File Structure

```bash
📂 Assignment 6
├── 📂 Assets/                       # Model and texture files
├── 📄 A6-Water.cpp                  # Main application logic
├── 📄 LoadShaders.cpp/.hpp         # Shader loading utilities
├── 📄 TextureMesh.cpp/.hpp         # Textured mesh class
├── 📄 textureLoader.cpp/.hpp       # BMP texture loading
├── 📄 WaterShader.*                # Vertex, fragment, tess, and geometry shaders
├── 📄 TextureShader.*              # Shaders for textured models
├── 📄 Makefile                     # Build script
└── 📄 README.md                    # This file
```

## Dependencies

- OpenGL
- GLFW
- GLEW
- GLM

## Known Issues

- **Fallback Warning**: macOS falls back to software vertex processing (SW vertex processing) for some shaders (especially tessellation and geometry).
- **Visual Output**: Water appears with a gradient but not fully realistic—suggests refinement needed in Gerstner wave parameters or displacement shader logic.
- **Texture Application**: Textured models "render" without errors, but it doesn't actually render onto the window. I didn't have time to fix this.