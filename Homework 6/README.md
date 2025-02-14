# **When rendering translucent (semi-transparent) objects, why must you render objects further away from the camera before objects closer to the camera?**

When rendering translucent (semi-transparent) obnjects, you must render objects further away from the camera before objects closer to the camera for a few reasons:

1. **Blending in OpenGL is non-commutative**
    - The blending funciton used (`GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA`) deteriens the final colour by blending the new fragment colouir with the existing colour in the framebuffer.
    - If a closer translucent object is drawn before a farther object, it blends with the deault background, ignoring the farther object.
2. **Depth buffer interference**
    - if depth testing (`glEnable(GL_DEPTH_TEST`)) is enabled, closer fragments overwrite farther fragments.
    - However, depth writes must be disabled for transparency using `glDEPTHMASK(GL_FALSE`), ensuring that translucent objects don't prevent further objects from rendering.
3. **Transparency requires manual sorting**
    - Unlike opaque objects, where Z_buffering handles visibility, transparent objects require manual sorting in a back-to-front order.
    - This ensures that the background is drawn first, and transparency layers ocrrectly stack on top.

## **First code segment**
```cpp
glMatrixMode(GL_PROJECTION);
glm::mat4 P = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);
glLoadMatrixf(glm::value_ptr(P));

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Background (further away)
    glVertex3f(0.0f, 1.0f, -3.0f);
    glVertex3f(-1.0f, 1.0f, -3.0f);
    glVertex3f(1.0f, -1.0f, -3.0f);

    glVertex3f(0.0f, 1.0f, -3.0f);
    glVertex3f(1.0f, -1.0f, -3.0f);
    glVertex3f(-1.0f, -1.0f, -3.0f);
glEnd();

glColor4f(0.0f, 0.0f, 1.0f, 0.3f); // Foreground (closer to the camera)
glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, 0.0f, -5.0f);
    glVertex3f(-0.5f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, -5.0f);

    glVertex3f(1.0f, 0.0f, -5.0f);
    glVertex3f(-0.5f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, -5.0f);
glEnd();
```
- Works
- The background object (further away) is drawn first.
- The foreground translucent object is drawn after the background, allowing proper alpha blending.
- Since OpenGL belnds new fragments with existing framebuffer colours, this order ensures that the background colours are properly factored into the final colour.
- Transparency is cumulative, meaning closer objects modify the already belnded colours behind them.

## **Second code segment**
```cpp
glMatrixMode(GL_PROJECTION);
glm::mat4 P = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);
glLoadMatrixf(glm::value_ptr(P));

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glBegin(GL_TRIANGLES);
    glColor4f(0.0f, 0.0f, 1.0f, 0.3f); // Foreground (closer to the camera)
    glVertex3f(-0.5f, 0.0f, -5.0f);
    glVertex3f(-0.5f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, -5.0f);

    glVertex3f(1.0f, 0.0f, -5.0f);
    glVertex3f(-0.5f, -1.0f, -5.0f);
    glVertex3f(1.0f, -1.0f, -5.0f);
glEnd();

glColor4f(1.0f, 0.0f, 0.0f, 0.5f); // Background (further away)
glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, -3.0f);
    glVertex3f(-1.0f, 1.0f, -3.0f);
    glVertex3f(1.0f, -1.0f, -3.0f);

    glVertex3f(0.0f, 1.0f, -3.0f);
    glVertex3f(1.0f, -1.0f, -3.0f);
    glVertex3f(-1.0f, -1.0f, -3.0f);
glEnd();
```
- Doesn't work
- The foreground (closer) colour is drawn first.
- The background object is drawn after, completely overwriting the foreground's blending effect.
- Since OpenGL blends each fragment with the current framebuffer state, the foreground object never has a chance to mix with the background because it wasn't drawn yet.

# **Why is the default value for glClearDepth equal to 1?**

## **The purpose of the depth buffer**
  - The depth buffer sotres depth values (Z_values) for each pixel to determine which fragments are in front and should be rendered.
  - When a new fragments is processed, OpenGL compares its depth value witht he value already stored in the depth buffer (using a depth function like `GL_LESS` or `GL_GREATER`).
  - If the new fragment "passes" the depth test, it replaces the current value in the buffer, ensuring that only the closest visible surfaces are drawn.

## **How depth values are assigned to fragments**
  - After transformation and projection, frasgment depth valeus are mapped to Normalized Device Coordinates (NDC).
  - In NDC space, the depth range is mapped to $[-1,1]$, but OpenGL remaps this range intot he depth buffer range $[0,1]$ (in standard depth mode).
  - The near clipping plane is mapped to `0.0` (closest to the camera).
  - The far clipping plane is mapped to `1.0` (furthest from the camera).

## **Why `glClearDepth(1.0)` is the default**
  - When clearing the depth buffer at the beginning of a new frame, we want to reset all depth values to the "farthest possible" depth.
    - The ensures that any object rendered int he scene will be closer than this initial value, allowing proper depth comparisons.
  - Since the far plane is ampped to 1.0 int he depth buffer, setting the default clear value to 1.0 makes sense.
    - It means that, initially, all pixels are set to "infinately far" (maximum depth), so any actual geometry will pass the depth test and be drawn.

## **What would happen if `glClearDepth(0.0)**
  - If we cleared the depth buffer with `glClearDepth(0.0)`, every pixel would intiially have the minimum depth value (clsoest possible).
  - This would cause depth tests with `GL_LESS` (default depth function) to fail, since new fragments would have greater depth values and would not be drawn.
  - The result is that only objects at the near clipping plane (depth = 0) would be rendered, and everything else would be hidden.

## **Sources**
  - [Khronos](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glClearDepth.xhtml)
  - [Learn OpenGL](https://learnopengl.com/)
  - Not a source but check out this license [here](https://www.opengl-tutorial.org/download/). Also read the **Forget Everything** part of one of their [tutorials](https://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/).

# Question 3 and 4 Output
<img src="Screenshot 2025-02-14 at 12.17.18.png" alt="Triangle Output" width="500">
