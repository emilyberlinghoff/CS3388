# Bezier Spline Editor

## Overview

The Bezier Spline Editor is an interactive application that allows users to create and manipulate a Bezier curve using control points and nodes. Users can add, move, and delete points to dynamically modify the curve. The program is built with C++ and OpenGL (GLFW).

## Features
- **Create Bezier Curves** – Click to add points and form a smooth curve.
- **Move Nodes & Control Points** – Drag nodes (green) and control points (red) to reshape the curve.
- **Undo (Z Key)** – Removes the last added node.
- **Clear (E Key)** – Clears all nodes and resets the canvas.
- **Anti-Aliasing (4x MSAA)** – Smooth rendering of curves.
- **Command-Line Arguments** – Customize window size on launch.

## Installation & Compilation

### Prerequisites

- C++ Compiler (g++ or Clang)
- GLFW (Install using Homebrew or APT)

### MacOS Installation

```bash
brew install glfw
```

### Ubuntu/Linux Installation

```bash
sudo apt update
sudo apt install libglfw3 libglfw3-dev
```

### Compiling the Program

```bash
g++ -std=c++11 -DGL_SILENCE_DEPRECATION -o bezier bezier.cpp -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL
```

## Usage

### Launching the Application

```bash
./bezier [width] [height]
```

Example:

```bash
./bezier 1024 768
```

If no resolution is specified, it defaults to ****800x600**.

## Controls

- **Left Click** – Add a new node (with control points).
- **Drag Green Nodes** – Move the position of curve points.
- **Drag Red Control Points** – Adjust curve smoothness.
- **Z Key** – Undo last added node.
- **E Key** – Clear all nodes.

## Notes

- Nodes are green, and their control points (handles) are red.
- The viewport and projection matrix are automatically set to match window size.
- Handles are automatically placed when adding new nodes, but can be dragged to refine the curve.
