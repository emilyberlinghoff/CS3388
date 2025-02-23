#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>

// Struct for a 2D point
struct Point {
    float x, y;
};

// Struct for a node (a point with optional control handles)
struct Node : Point {
    bool hasHandle1 = false, hasHandle2 = false; // Flags to indicate control handles exist
    Point handle1, handle2; // Control handle positions
};

// Global variables
std::vector<Node> nodes; // Stores all nodes in the spline
bool draggingNode = false, draggingHandle = false;
int draggedIndex = -1, draggedHandleIndex = -1;
int screenWidth = 800, screenHeight = 600;  // Default window size

// Function to initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_MULTISAMPLE);  // Enable 4x MSAA (Anti-Aliasing)
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glViewport(0, 0, screenWidth, screenHeight);
}

// Function to draw a small circle at (cx, cy) with a given radius
void drawCircle(float cx, float cy, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 20; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(20);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}

// Function to draw the Bezier curve using cubic interpolation
void drawBezierCurve() {
    if (nodes.size() < 2) return; // Need at least 2 nodes to draw a curve

    glLineWidth(2.0f);
    glColor3f(0, 0, 1); // Set curve color to blue
    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i < nodes.size() - 1; ++i) {
        Node &p0 = nodes[i];
        Node &p1 = nodes[i + 1];

        // Control points for cubic interpolation
        Point c1 = p0.hasHandle2 ? p0.handle2 : p0;
        Point c2 = p1.hasHandle1 ? p1.handle1 : p1;

        // Generate Bezier curve points
        for (float t = 0; t <= 1; t += 0.01f) { // Sample curve at small intervals
            float x = pow(1 - t, 3) * p0.x +
                      3 * pow(1 - t, 2) * t * c1.x +
                      3 * (1 - t) * t * t * c2.x +
                      t * t * t * p1.x;
            float y = pow(1 - t, 3) * p0.y +
                      3 * pow(1 - t, 2) * t * c1.y +
                      3 * (1 - t) * t * t * c2.y +
                      t * t * t * p1.y;
            glVertex2f(x, y);
        }
    }
    glEnd();
}

// Function to draw red control lines between nodes and handles
void drawHandles() {
    glColor3f(1, 0, 0); // Red color for handles
    glBegin(GL_LINES);

    for (auto &node : nodes) {
        if (node.hasHandle1) {
            glVertex2f(node.x, node.y);
            glVertex2f(node.handle1.x, node.handle1.y);
        }
        if (node.hasHandle2) {
            glVertex2f(node.x, node.y);
            glVertex2f(node.handle2.x, node.handle2.y);
        }
    }

    glEnd();
}

// Function to draw nodes and control handles
void drawNodes() {
    glColor3f(0, 1, 0); // Green color for nodes
    for (auto &node : nodes) drawCircle(node.x, node.y, 5);

    glColor3f(1, 0, 0); // Red color for control points
    for (auto &node : nodes) {
        if (node.hasHandle1) drawCircle(node.handle1.x, node.handle1.y, 4);
        if (node.hasHandle2) drawCircle(node.handle2.x, node.handle2.y, 4);
    }
}

// Function to render everything
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    drawBezierCurve(); // Draw the spline
    drawHandles(); // Draw handle connections
    drawNodes(); // Draw nodes and control points
    glfwSwapBuffers(glfwGetCurrentContext()); // Swap buffers
}

// Function to handle mouse clicks
void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    my = screenHeight - my; // Convert to OpenGL coordinates

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (fabs(mx - nodes[i].x) < 5 && fabs(my - nodes[i].y) < 5) {
                draggingNode = true;
                draggedIndex = i;
                return;
            }
            if (nodes[i].hasHandle1 && fabs(mx - nodes[i].handle1.x) < 4 && fabs(my - nodes[i].handle1.y) < 4) {
                draggingHandle = true;
                draggedIndex = i;
                draggedHandleIndex = 1;
                return;
            }
            if (nodes[i].hasHandle2 && fabs(mx - nodes[i].handle2.x) < 4 && fabs(my - nodes[i].handle2.y) < 4) {
                draggingHandle = true;
                draggedIndex = i;
                draggedHandleIndex = 2;
                return;
            }
        }

        // Add a new node with control handles
        Node newNode;
        newNode.x = static_cast<float>(mx);
        newNode.y = static_cast<float>(my);

        if (!nodes.empty()) {
            newNode.hasHandle1 = true;
            newNode.handle1.x = mx - 40; // Set default control points
            newNode.handle1.y = my;

            nodes.back().hasHandle2 = true;
            nodes.back().handle2.x = nodes.back().x + 40;
            nodes.back().handle2.y = nodes.back().y;
        }

        nodes.push_back(newNode);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        draggingNode = false;
        draggingHandle = false;
        draggedIndex = -1;
        draggedHandleIndex = -1;
    }
}

// Function to handle mouse movement (dragging nodes or handles)
void mouseMoveCallback(GLFWwindow* window, double mx, double my) {
    my = screenHeight - my;

    if (draggingNode && draggedIndex != -1) {
        nodes[draggedIndex].x = mx;
        nodes[draggedIndex].y = my;
    }

    if (draggingHandle && draggedIndex != -1) {
        if (draggedHandleIndex == 1) {
            nodes[draggedIndex].handle1.x = mx;
            nodes[draggedIndex].handle1.y = my;
        } else if (draggedHandleIndex == 2) {
            nodes[draggedIndex].handle2.x = mx;
            nodes[draggedIndex].handle2.y = my;
        }
    }
}

// Keyboard Callback for clearing and undoing
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_E) {
            nodes.clear();
        } else if (key == GLFW_KEY_Z && !nodes.empty()) {
            nodes.pop_back();
        }
    }
}

// Main function
int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bezier Spline Editor", NULL, NULL);
    glfwMakeContextCurrent(window);
    initOpenGL();

    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window)) {
        renderScene();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
