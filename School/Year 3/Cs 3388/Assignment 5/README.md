# Assignment 5 - Marching Cubes with OpenGL

## Overview
This project implements the Marching Cubs algorithm to generatre traignle meshes from scalar fields and render themusing non-trivial shaders with OpenGL. It includes interactive camera manipulation ushing spherical coordinates, lighting shaders, and functionality to export generated meshes to PLY files.

## Key Functionalities

### Camera manipulation
- **Rotation**: Mouse click-and-drag horizontally to modify θ (azimuth) and vertically to modify ϕ (elevation).
- **Zooming**: Use the up/down arrow keys to decrease/incrase camera distance (`r`) from the origin.
**Initialization**: The camera starts at position `(5, 5, 5)` looking towards the origin `(0, 0, 0)`.

### Marching Cubes Implementation
- **Function Signature**:
    ```cpp
    MarchingCubes(
    std::function<float(float, float, float)> f,
    float isovalue,
    float min,
    float max,
    float stepsize);
    ```
    - `f`: Scalar field function.
    - `isovalue`: THreshold defining the boundary surface.
    - `min` and `max`: Boudning valeus defining the marching volume.
    - `stepsize`: REsolution of the marching grid.

### Vertex Normal Calculation
- **Compute Normals**: Generate normalized normals per vertex assuming a counter-clockwise winding order. Each vertex is repeated for each vertex of a triangle.

### Mesh Export
- Generated meshes are exported to a PLY file, including vertex positions and computed normals. You can find this in `build/output.ply`.

### Rendering Details
- **Bounding box**: Render a wireframe bounding box from `(min, min, min)` to `(max, max, max)`.
- **Coordinate Axes**: Draw positive X, Y, and Z axes originating at `(min, min, min)`.
- **Shader Implementation**:
    - **Vertex Shader**: Computes required vectors and passes interpolated valeus to the fragment shader.
    - **Fragment Shader**: Calcualtes colour using ambient, diffuse, and speculat components with:
        - Ambient colour `(0.2, 0.2, 0.2)`
        - Specular colour `(1.0, 1.0, 1.0)`
        - Shininess factor `64`

## Controls
| Input          | Action                          |
|----------------|---------------------------------|
| Mouse Drag     | Rotate camera                   |
| Up Arrow Key   | Move camera closer to origin    |
| Down Arrow Key | Move camera further from origin |

## Compilation and Running
To build and run the application:
```bash
mkdir build && cd build
cmake ..
make
./marching_cubes
```
## File Structure
```bash
📂 Assignment 5
├── 📂 include/
│   ├── 📄 camera.hpp           # Camera class definition
│   ├── 📄 marching_cubes.hpp   # Marching Cubes class definition
│   ├── 📄 rendering.hpp        # Rendering utilities
│   ├── 📄 shaders.hpp          # Shader management utilities
│   ├── 📄 TriTable.hpp         # Marching Cubes lookup tables
│   └── 📄 utils.hpp            # Utility function declarations
├── 📂 shaders/
│   ├── 📄 vertex_shader.glsl   # Vertex shader code
│   └── 📄 fragment_shader.glsl # Fragment shader code
├── 📂 src/
│   ├── 📄 camera.cpp           # Camera control and movement
│   ├── 📄 main.cpp             # Main application loop
│   ├── 📄 marching_cubes.cpp   # Marching Cubes algorithm implementation
│   ├── 📄 rendering.cpp        # OpenGL rendering setup
│   ├── 📄 shaders.cpp          # Shader loading and compilation
│   └── 📄 utils.cpp            # Utility functions (e.g., normals computation)
├── 📄 CMakeLists.txt           # CMake configuration file
└── 📄 README.md                # This file
```

## Lookup Tables
The Marching Cubes algorithm utilizes two essential lookup tables defined in `TriTable.hpp`:
- **edge-to-vertex**: DEfines the relationship between edges and vertices.
- **marching_cubes_lut*: Contains recomputed triangle vertex indicies for all 256 possible cube configurations.
- **vertTable**: Provides ertex interpolation points.
These tables facilitate efficient mesh generation and rendering.

## Dependencies
- OpenGL
- GLFW (for window and input management)
- GLM (for mathematics)

## Issues
- Despite using the same formula, my surfaces don't look like the correct version. Both the shape and the steps are different.
- The coordinate axes are there, but you can't see them. I have a feeling they are hiding inslide the sides of the box but I didn't have enough time to debug this.