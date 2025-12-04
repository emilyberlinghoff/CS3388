# OpenGL Triangle Rendering Program

This program renders a simple black triangle on a white background using OpenGL. It demonstrates the basics of setting up a rendering context and drawing shapes in OpenGL using the GLFW library.

---

## Prerequisites

Ensure the following tools and libraries are installed on your macOS system:

1. **Xcode Command Line Tools** (for `g++`):
   ```bash
   xcode-select --install
   ```

2. **Homebrew Package Manager** (if not installed, visit [Homebrew](https://brew.sh)):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

3. **Install Dependencies**:
   - GLFW:
     ```bash
     brew install glfw
     ```
   - (Optional) FreeGLUT (if using GLUT):
     ```bash
     brew install freeglut
     ```

---

## Installation and Compilation

1. Clone or download the source file `triangle.cpp`.

2. Compile the program:
   ```bash
   g++ -o triangle_program triangle.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL
   ```

3. Run the program:
   ```bash
   ./triangle_program
   ```

---

## Output

When the program runs successfully, a window titled **"Hello World"** will appear. It will display a black triangle in the center on a white background.

---

## Screenshot

Upload a screenshot of the program's output below:

**Screenshot Placeholder:**
![Program Output Screenshot](./screenshot.png)

---

## Troubleshooting

### Common Issues:
1. **`glfw3.h not found`:**
   Ensure GLFW is installed and the paths are correctly specified in the compilation command:
   ```bash
   brew install glfw
   g++ -o triangle_program triangle.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL
   ```

2. **Deprecation Warnings on macOS:**
   macOS deprecates OpenGL APIs. Suppress warnings using:
   ```bash
   -DGL_SILENCE_DEPRECATION
   ```

3. **Library Linking Issues:**
   Verify Homebrew paths for `GLFW` libraries:
   ```bash
   ls /opt/homebrew/include/GLFW/glfw3.h
   ls /opt/homebrew/lib/libglfw*
   ```
