# CS3388B - Assignment 2: OpenGL Implementations

This repository contains solutions for CS3388B Assignment 2, implementing two OpenGL-based programs.

## 1. Rotating Dog
### Description
- Reads a poly-line drawing from `dog.txt`
- Draws eight instances of the shape around a circle of radius 25, centered at (30,30)
- Each instance rotates counterclockwise over time

### Compilation and Execution
#### Compile:
```bash
g++ -std=c++11 -o question1 question1.cpp \
    -I/opt/homebrew/Cellar/glfw/3.4/include \
    -L/opt/homebrew/Cellar/glfw/3.4/lib \
    -lglfw -framework OpenGL
```
#### Run:
```bash
./question1
```
Ensure dog.txt is present in the execution directory.

## 2. Dot Plot Algorithm
### Description
- Generates a dot plot within a square (-1, -1) to (1, 1)
- Iteratively computes midpoints between a chosen point and a selected corner
- Supports up to 5,000,000 points efficiently

### Compilation and Execution
#### Compile:
```bash
g++ -std=c++11 -o question2 question2.cpp \
    -I/opt/homebrew/Cellar/glfw/3.4/include \
    -L/opt/homebrew/Cellar/glfw/3.4/lib \
    -lglfw -framework OpenGL
```
#### Run:
```bash
./question2 <N> <screen_width> <screen_height>
```
#### Example:
```bash
./question2 1000000 800 800
```

## Dependencies
Install required libraries using:
```bash
brew install glfw glm
```

## Repository Structure
```bash
CS3388B-Assignment2/
 ├── README.md
 ├── question1.cpp
 ├── question2.cpp
 ├── dog.txt
```

## Author
Emily Berlinghoff
Western University, CS3388B - Winter 2025
