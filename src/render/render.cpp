#include <iostream> // For debugging or logging (if needed)
#include "fmt/format.h" // For formatted output (if used elsewhere)
#include "imgui.h" // Dear ImGui library
#include "implot.h" // ImPlot library

#include "render.hpp" // Header file for WindowClass and render function

/**
 * @brief Draws a UI element with the specified label.
 * 
 * This method sets up an ImGui window with predefined size, position, and flags.
 * The window is labeled using the provided `label` parameter.
 * 
 * @param label The label to display for the UI element.
 */
void WindowClass::Draw(std::string_view label)
{
    // Define window properties
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    constexpr static auto window_size = ImVec2(1280.0F, 720.0F); // Window size
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);       // Window position

    // Set the size and position of the next window
    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    // Begin the ImGui window with the specified label
    ImGui::Begin(label.data(), nullptr, window_flags);

    // End the ImGui window
    ImGui::End();
}

/**
 * @brief Destructor for the WindowClass.
 * 
 * Cleans up any resources associated with the window or rendering context.
 */
WindowClass::~WindowClass()
{
    // Example cleanup logic (if needed)
    // If using a library like GLFW, you might destroy the window here:
    // glfwDestroyWindow(static_cast<GLFWwindow*>(m_windowHandle));
    // std::cout << "WindowClass resources cleaned up." << std::endl;

    // For now, just log that the destructor was called
    std::cout << "WindowClass destructor called. Resources cleaned up." << std::endl;
}

/**
 * @brief Renders the UI using the provided WindowClass object.
 * 
 * This function calls the `Draw` method of the `WindowClass` object
 * to render the UI elements.
 * 
 * @param window_obj Reference to a WindowClass object used for rendering.
 */
void render(WindowClass &window_obj)
{
    // Call the Draw method with a hardcoded label
    window_obj.Draw("*Label*");
}
