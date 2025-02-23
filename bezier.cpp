#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <iostream>

// Structs for Points and Nodes
struct Point {
    float x, y;
};

struct Node : Point {
    bool hasHandle1 = false, hasHandle2 = false;
    Point handle1, handle2;
};

// Global Variables
std::vector<Node> nodes;
bool draggingNode = false, draggingHandle = false;
int draggedIndex = -1, draggedHandleIndex = -1;
int screenWidth = 800, screenHeight = 600;  // Default values, updated via command-line args

// Function to Initialize OpenGL Settings
void initOpenGL() {
    glEnable(GL_MULTISAMPLE);  // Enable 4x MSAA
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glViewport(0, 0, screenWidth, screenHeight);
}

// Function to Draw a Circle
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

// Function to Draw the Bezier Curve
void drawBezierCurve() {
    if (nodes.size() < 2) return;

    glLineWidth(2.0f);
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i < nodes.size() - 1; ++i) {
        Node &p0 = nodes[i];
        Node &p1 = nodes[i + 1];
        Point c1 = p0.hasHandle2 ? p0.handle2 : p0;
        Point c2 = p1.hasHandle1 ? p1.handle1 : p1;

        for (float t = 0; t <= 1; t += 0.01f) {
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

// Function to Draw Handles
void drawHandles() {
    glColor3f(1, 0, 0);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
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
    glDisable(GL_LINE_STIPPLE);
}

// Function to Draw Nodes
void drawNodes() {
    glColor3f(0, 1, 0);
    for (auto &node : nodes) drawCircle(node.x, node.y, 5);

    glColor3f(1, 0, 0);
    for (auto &node : nodes) {
        if (node.hasHandle1) drawCircle(node.handle1.x, node.handle1.y, 4);
        if (node.hasHandle2) drawCircle(node.handle2.x, node.handle2.y, 4);
    }
}

// Render Scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBezierCurve();
    drawHandles();
    drawNodes();
    glfwSwapBuffers(glfwGetCurrentContext());
}

// Mouse Click Callback
void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    my = screenHeight - my;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (fabs(mx - nodes[i].x) < 5 && fabs(my - nodes[i].y) < 5) {
                draggingNode = true;
                draggedIndex = i;
                return;
            }
        }

        Node newNode;
        newNode.x = static_cast<float>(mx);
        newNode.y = static_cast<float>(my);
        if (!nodes.empty()) {
            newNode.hasHandle1 = true;
            newNode.handle1.x = mx;
            newNode.handle1.y = my + 50;
            nodes.back().hasHandle2 = true;
            nodes.back().handle2.x = nodes.back().x;
            nodes.back().handle2.y = nodes.back().y - 50;
        }
        nodes.push_back(newNode);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        draggingNode = false;
        draggedIndex = -1;
    }
}

// Mouse Move Callback
void mouseMoveCallback(GLFWwindow* window, double mx, double my) {
    my = screenHeight - my;

    if (draggingNode && draggedIndex != -1) {
        nodes[draggedIndex].x = mx;
        nodes[draggedIndex].y = my;
    }
}

// Key Callback
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        nodes.clear();
    }
}

// Main Function
int main(int argc, char** argv) {
    // Parse command-line arguments
    if (argc == 3) {
        screenWidth = std::stoi(argv[1]);
        screenHeight = std::stoi(argv[2]);
    } else {
        std::cerr << "Usage: " << argv[0] << " <width> <height>\n";
        std::cerr << "Using default: " << screenWidth << "x" << screenHeight << "\n";
    }

    // Initialize GLFW
    if (!glfwInit()) return -1;

    // Enable 4x MSAA for Anti-Aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create Window
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Bezier Spline Editor", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    initOpenGL();  // Setup projection and viewport

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