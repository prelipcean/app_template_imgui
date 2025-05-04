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
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    ImGui::Begin(label.data(), nullptr, window_flags);

    ImGui::Text("Hello, %s!", label.data()); // Display the label in the window
    
    /* Below lines are copied from:
    https://github.com/ocornut/imgui/blob/3543dfda953beefd9add1316328e2c7cfb4aa637/imgui_demo.cpp
    */
    ImGui::SeparatorText("ABOUT THIS DEMO:");
    ImGui::BulletText("Sections below are demonstrating many aspects of the library.");
    ImGui::BulletText("The \"Examples\" menu above leads to more demo contents.");
    ImGui::BulletText("The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                      "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");

    ImGui::SeparatorText("PROGRAMMER GUIDE:");
    ImGui::BulletText("See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
    ImGui::BulletText("See comments in imgui.cpp.");
    ImGui::BulletText("See example applications in the examples/ folder.");
    ImGui::BulletText("Read the FAQ at ");
    ImGui::SameLine(0, 0);
    ImGui::TextLinkOpenURL("https://www.dearimgui.com/faq/");
    ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
    ImGui::BulletText("Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");

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
