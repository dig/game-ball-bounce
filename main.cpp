#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>

#define DEG2RAD 3.14159 / 180
#define BALL_SIZE 100

float random()
{
    return rand() / (float) RAND_MAX;
}

int randomInt(int min, int max)
{
    return rand()%(max - min + 1) + min;
}

void drawCircle2f(float x, float y, float radius)
{
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 360; i++) {
        float degInRad = i * DEG2RAD;
        glVertex2f(x + cos(degInRad) * radius, y + sin(degInRad) * radius);
    }

    glEnd();
}

float distanceSqr(float x, float y, float x1, float y1)
{
    float dx = x1 - x;
    float dy = y1 - y;
    return (dx * dx) + (dy * dy);
}

float distance(float x, float y, float x1, float y1)
{
    return sqrt(distanceSqr(x, y, x1, y1));
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Ball Bounce", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    int bx = width / 2, by = height / 2;
    int bvx = 5, bvy = 3;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        bx += bvx;
        by += bvy;

        if (bx - BALL_SIZE <= 0 || bx + BALL_SIZE >= width) {
            bvx = -bvx;
        } else if (by - BALL_SIZE <= 0 || by + BALL_SIZE >= height) {
            bvy = -bvy;
        }

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float distanceToBall = distance(bx, by, xpos, ypos);
        if (distanceToBall <= BALL_SIZE && distanceToBall >= BALL_SIZE - 5) {
            bvx = -bvx;
            bvy = -bvy;
        } else if (distanceToBall <= BALL_SIZE) {
            bvx = 0;
            bvy = 0;
        } else if (bvx == 0 && bvy == 0 && distanceToBall >= BALL_SIZE) {
            bvx = randomInt(1, 5);
            bvy = randomInt(1, 5);
        }

        glLoadIdentity();
        glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);

        drawCircle2f(bx, by, BALL_SIZE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
