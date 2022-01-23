#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "glad.h"
#include "GLFW/glfw3.h"

static int Random(int min, int max)
{
    time_t t;
    srand((unsigned int)time(&t));
    return (rand()%(abs(max - min) + 1) + min);
}

static void glfw_error_callback(int code, const char* msg)
{
    printf("GLFW ERROR: [%d] %s\n", code, msg);
}

int main(void)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() == GLFW_FALSE)
    {
        printf("Failed to initialize GLFW\n");
        return 1;
    }
    printf("GLFW: %s\n", glfwGetVersionString());

    glfwTerminate();
    return 0;
}
