This directory contains three OpenGL C++ programs that implement shader-based exercises. Each program demonstrates a different aspect of using shaders for rendering triangles.

# Overview

- **P7-TODO.cpp**
    *Exercise 1 – Debugging with Shaders:*
    Implements a vertex shader that accepts vertex positions and colors, and a fragment shader that outputs black if the interpolated vertex color’s red component is greater than 0.5. Otherwise, it outputs the vertex color as is.
- **P7-TODO2.cpp**
    *Exercise 2 – Debugging with Shaders, Part 2:*
    Implements a vertex shader that accepts vertex positions and texture coordinates. The fragment shader uses the interpolated texture coordinates to set the output color: it assigns the U coordinate to the red channel, the V coordinate to the green channel, sets the blue channel to 0, and alpha to 1.
- **P7-TODO3.cpp**
    *Exercise 3 – Exploring Textures with Shaders:*
    Implements a vertex shader that accepts vertex positions and texture coordinates. The fragment shader uses four uniform variables (two sampler2Ds: `tex1` and `tex2`; and two floats: `blend1` and `blend2`) to blend two textures. It samples each texture using the UV coordinates and outputs the final color computed as:
    **outputColor = blend1 * color1 + blend2 * color2**.
    
## Dependencies

- OpenGL
- GLEW
- GLFW
- GLM

On macOS, you can install these via Homebrew:

```bash
brew install glfw glew glm
```

# Building the Programs

Use the following commands to compile each program from the command line. (Make sure your compiler supports at least C++11.)

## P7-TODO.cpp
```bash
g++ P7-TODO.cpp -o shader_program -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL -std=c++11
```
Run with:
```bash
./shader_program
```

## P7-TODO2.cpp
```bash
g++ P7-TODO2.cpp -o shader_program2 -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL -std=c++11
```
Run with:
```bash
./shader_program2
```

## P7-TODO3.cpp
```bash
g++ P7-TODO3.cpp -o shader_program3 -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL -std=c++11
```
Run with:
```bash
./shader_program3
```

# Program Details

## P7-TODO.cpp
- **Purpose**: Visualize shader debugging by outputting black if a vertex color’s red component exceeds 0.5.
- **Shaders**:
    - **Vertex Shader**: Passes vertex positions and colors to the fragment shader.
    - **Fragment Shader**: Uses an if/else to check the red component and outputs either black or the original color.

## P7-TODO2.cpp
- **Purpose**: Provide visual feedback using texture coordinates.
- **Shaders**:
    - **Vertex Shader**: Passes vertex positions and texture coordinates.
    - **Fragment Shader**: Sets the output color using the UV coordinates:
        - Red ← U coordinate
        - Green ← V coordinate
        - Blue = 0, Alpha = 1

## P7-TODO3.cpp
- **Purpose**: Blend two textures using shaders.
- **Texture Setup**:
    Two procedural textures are generated:
    - **Texture 1**: Green gradient.
    - **Texture 2**: Blue gradient.
- **Shaders:**
    - **Vertex Shader**: Passes vertex positions and texture coordinates.
    - **Fragment Shader**: Accepts four uniforms (`tex1`, `tex2`, `blend1`, and `blend2`). It samples both textures using the provided UV coordinates and computes the final fragment color using the formula:
    ```bash
    gl_FragColor = blend1 * texture2D(tex1, UV) + blend2 * texture2D(tex2, UV);
    ```