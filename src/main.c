#include "sandsim.h"

static Sandsim* sandsim = NULL;

static int Random(int min, int max)
{
    time_t t;
    srand((unsigned int)time(&t));
    return (rand()%(abs(max - min) + 1) + min);
}


#pragma region ====================   GLFW CALLBACKS   ==========================================

static void gl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    printf("GL ERROR: %s\n", message);
}

static void glfw_error_callback(int code, const char* msg)
{
    printf("GLFW ERROR: [%d] %s\n", code, msg);
}

static void glfw_framebuffer_size_callback(GLFWwindow* win, int w, int h)
{
    sandsim->fbSize = (vec2s){ {w, h} };
    glViewport(0, 0, w, h);
}

static void glfw_windowsize_callback(GLFWwindow* win, int w, int h)
{
    sandsim->wSize = (vec2s){ {w, h} };
}

static void glfw_key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
    if (key < 0) return;

    switch (action)
    {
    case GLFW_PRESS:
        sandsim->keys[key].down = true;
        break;
    case GLFW_RELEASE:
        sandsim->keys[key].down = false;
        break;
    default:
        break;
    }
}

static void glfw_char_callback(GLFWwindow* win, unsigned int codepoint)
{
    sandsim->lastChar = codepoint;
}

static void glfw_mouse_button_callback(GLFWwindow* win, int button, int action, int mods)
{
    if (button < 0) return;

    switch (action)
    {
    case GLFW_PRESS:
        sandsim->mouse.buttons[button].down = true;
        break;
    case GLFW_RELEASE:
        sandsim->mouse.buttons[button].down = false;
        break;
    default:
        break;
    }
}

static void glfw_scroll_callback(GLFWwindow* win, double xoff, double yoff)
{
    sandsim->mouse.wheelDelta = yoff;
}

#pragma endregion

static void updateButtons(size_t count, Button* buttons)
{
    for (size_t i = 0; i < count; i++)
    {
        buttons[i].pressed = buttons[i].down && !buttons[i].last;
        buttons[i].last = buttons[i].down;
    }
}

static void processInput()
{
    updateButtons(GLFW_KEY_LAST, sandsim->keys);
    updateButtons(GLFW_MOUSE_BUTTON_LAST, sandsim->mouse.buttons);
    double xpos, ypos;
    glfwGetCursorPos(sandsim->window, &xpos, &ypos);
    vec2s newPos = (vec2s){ {(float)xpos, (float)ypos} };
    sandsim->mouse.delta = glms_vec2_sub(newPos, sandsim->mouse.position);
    sandsim->mouse.position = newPos;
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

    sandsim = calloc(1, sizeof(Sandsim));
    assert(sandsim != NULL);
    sandsim->wSize = (vec2s){ {800.0f, 600.0f} };
    sandsim->fullScreen = false;

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // DEBUG
    sandsim->window = glfwCreateWindow(sandsim->wSize.x, sandsim->wSize.y, "Sandsim", NULL, NULL);
    assert(sandsim->window != NULL);
    
    //window size, fullscreen
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vmode = glfwGetVideoMode(monitor);
    int xpos = 0;
    int ypos = 0;
    if (!sandsim->fullScreen)
    {
        xpos = (vmode->width - sandsim->wSize.x) / 2;
        ypos = (vmode->height - sandsim->wSize.y) / 2;
    }
    else {
        sandsim->wSize = (vec2s){ {(float)vmode->width, (float)vmode->height} };
    }
    glfwSetWindowMonitor(sandsim->window, sandsim->fullScreen ? monitor : NULL, xpos, ypos, sandsim->wSize.x, sandsim->wSize.y, GLFW_DONT_CARE);
    glfwShowWindow(sandsim->window);
    glfwMakeContextCurrent(sandsim->window);

    //load opengl
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    printf("GL: %s\n", glGetString(GL_VERSION));
    printf("GL: %s\n", glGetString(GL_RENDERER));
    printf("GL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#ifdef _DEBUG
    glDebugMessageCallback(gl_error_callback, NULL);
#endif // _DEBUG

    glfwSwapInterval(1);

    //glfw callbacks
    glfwSetFramebufferSizeCallback(sandsim->window, glfw_framebuffer_size_callback);
    glfwSetWindowSizeCallback(sandsim->window, glfw_windowsize_callback);
    //glfwSetCursorPosCallback(demo->window, demoCursorPos);
    glfwSetKeyCallback(sandsim->window, glfw_key_callback);
    glfwSetMouseButtonCallback(sandsim->window, glfw_mouse_button_callback);
    glfwSetCharCallback(sandsim->window, glfw_char_callback);
    glfwSetScrollCallback(sandsim->window, glfw_scroll_callback);

    int w, h;
    glfwGetFramebufferSize(sandsim->window, &w, &h);
    sandsim->fbSize = (vec2s){ {w,h} };
    glfwGetWindowSize(sandsim->window, &w, &h);
    sandsim->wSize = (vec2s){ {w,h} };

    glViewport(0, 0, sandsim->fbSize.x, sandsim->fbSize.y);
    glEnable(GL_DEPTH_TEST);

    //main loop
    sandsim->running = true;
    while (sandsim->running)
    {
        processInput();

        //update


        //render
        


        //reset for next frame
        sandsim->mouse.delta = GLMS_VEC2_ZERO;
        sandsim->mouse.wheelDelta = 0.0f;

        //poll & swap
        glfwSwapBuffers(sandsim->window);
        glfwPollEvents();

        if (glfwWindowShouldClose(sandsim->window) == GLFW_TRUE)
            sandsim->running = false;
    }

    if (sandsim)
    {
        glfwDestroyWindow(sandsim->window);
        free(sandsim);
        sandsim = NULL;
    }
    glfwTerminate();
    return 0;
}
