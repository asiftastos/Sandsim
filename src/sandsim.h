#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "cglm/struct.h"
#include "assets.h"

typedef struct Button
{
    bool down;
    bool last;
    bool pressed;
}Button;

typedef struct Mouse
{
    Button buttons[GLFW_MOUSE_BUTTON_LAST];
    vec2s position;
    vec2s delta;
    float wheelDelta;
}Mouse;

typedef struct Sandsim
{
    GLFWwindow* window;
    Mouse mouse;
    Button keys[GLFW_KEY_LAST];
    unsigned int lastChar;
    vec2s wSize;
    vec2s fbSize;
    bool running;
    bool fullScreen;

    Shader* shaderProgram;
    Pipeline* pipeline;
    unsigned int worldVao;
    unsigned int worldVbo;
    mat4s projection;
}Sandsim;