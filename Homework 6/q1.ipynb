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

## First code segment
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

## Second code segment
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
