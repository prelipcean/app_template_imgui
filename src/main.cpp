#include <cstdint>
#include <filesystem>

// ImGui and ImPlot includes
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include <imgui.h>
#include <implot.h>

// OpenGL and GLFW includes
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

// Project-specific includes
#include "render.hpp"

// Compatibility for MSVC
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// Window dimensions
constexpr auto WINDOW_WIDTH = std::uint32_t{1280};
constexpr auto WINDOW_HEIGHT = std::uint32_t{720};

// Namespace alias for filesystem
namespace fs = std::filesystem;

// Function declarations
static void glfw_error_callback(int error, const char *description);
void start_cycle();
void end_cycle(GLFWwindow *const window);

int main(int, char **)
{
    // Setup GLFW error callback
    glfwSetErrorCallback(glfw_error_callback);

    // Initialize GLFW
    if (!glfwInit())
    {
        return 1; // Exit if initialization fails
    }

    // Decide GL+GLSL versions based on platform
#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char *glsl_version = "#version 100"; // GL ES 2.0 + GLSL 100
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    const char *glsl_version = "#version 150"; // GL 3.2 + GLSL 150
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    const char *glsl_version = "#version 130"; // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    // Create a window with an OpenGL context
    auto *window = glfwCreateWindow(static_cast<std::int32_t>(WINDOW_WIDTH),
                                    static_cast<std::int32_t>(WINDOW_HEIGHT),
                                    "GUI Window",
                                    nullptr,
                                    nullptr);
    if (window == nullptr)
    {
        return 1; // Exit if window creation fails
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark(); // Use dark theme for ImGui

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Customize ImGui style
    auto &style = ImGui::GetStyle();
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(1.0, 1.0, 1.0, 1.0);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(1.0, 1.0, 1.0, 1.0);

    // Create an instance of the custom window class
    WindowClass window_obj;

    // Setup ImPlot context
    ImPlot::CreateContext();

    // Main application loop
    while (!glfwWindowShouldClose(window))
    {
        start_cycle(); // Start a new frame

        ImGui::NewFrame(); // Begin ImGui frame
        render(window_obj); // Render custom UI
        ImGui::Render(); // Finalize ImGui rendering

        end_cycle(window); // End the frame and swap buffers
    }

    // Cleanup ImPlot context
    ImPlot::DestroyContext();

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Destroy the GLFW window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0; // Exit successfully
}

// GLFW error callback function
void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// Start a new rendering cycle
void start_cycle()
{
    glfwPollEvents(); // Process events
    ImGui_ImplOpenGL3_NewFrame(); // Start OpenGL frame
    ImGui_ImplGlfw_NewFrame(); // Start GLFW frame
}

// End the rendering cycle and swap buffers
void end_cycle(GLFWwindow *const window)
{
    // Clear color for the window
    const auto clear_color =
        ImVec4(30.0F / 255.0F, 30.0F / 255.0F, 30.0F / 255.0F, 1.00f);

    // Get framebuffer size and set viewport
    int display_w = 0;
    int display_h = 0;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // Clear the screen
    glClearColor(clear_color.x * clear_color.w,
                 clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render ImGui draw data
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers
    glfwSwapBuffers(window);
}
