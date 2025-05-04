#include <iostream> // For debugging or logging (if needed)
#include "fmt/format.h" // For formatted output (if used elsewhere)
#include "imgui.h" // Dear ImGui library
#include "implot.h" // ImPlot library

#include "render.hpp" // Header file for WindowClass and render function

/**
 * @brief Constructor for the WindowClass.
 * 
 * Initializes the current path to the current working directory.
 */
WindowClass::WindowClass() : currentPath(fs::current_path())
{
    std::cout << "WindowClass initialized with current path: " << currentPath << std::endl;
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

    DrawMenu();    // Draw the menu section
    ImGui::Separator(); // Separator line between sections
    DrawContent(); // Draw the content section
    ImGui::Separator(); // Separator line between sections
    DrawActions(); // Draw the actions section
    ImGui::Separator(); // Separator line between sections
    DrawFilter();  // Draw the filter section

    // End the ImGui window
    ImGui::End();
}

/**
 * @brief Draws the menu section of the UI.
 * 
 * Displays navigation options, such as "Go Up" to navigate to the parent directory.
 */
void WindowClass::DrawMenu()
{
    if (ImGui::Button("Go Up"))
    {
        if (currentPath.has_parent_path())
        {
            currentPath = currentPath.parent_path();
        }
    }

    ImGui::SameLine();
    if (currentPath.empty())
    {
        ImGui::Text("Current directory: [Invalid Path]");
    }
    else
    {
        ImGui::Text("Current directory: %s", currentPath.string().c_str());
    }
}

/**
 * @brief Draws the content section of the UI.
 * 
 * Lists files and directories in the current path. Allows selection of entries.
 */
void WindowClass::DrawContent()
{
    ImGui::Text("DrawContent"); // Placeholder for content drawing logic
}

/**
 * @brief Draws the actions section of the UI.
 * 
 * Displays actions (e.g., Open, Rename, Delete) for the selected file or directory.
 */
void WindowClass::DrawActions()
{
    ImGui::Text("DrawActions"); // Placeholder for actions drawing logic 
}

/**
 * @brief Draws the filter section of the UI.
 * 
 * Allows filtering files by extension and displays the count of matching files.
 */
void WindowClass::DrawFilter()
{
    ImGui::Text("DrawFilter"); // Placeholder for filter drawing logic
}

/**
 * @brief Opens the selected file with the default editor.
 */
void WindowClass::openFileWithDefaultEditor()
{

}

/**
 * @brief Displays a popup for renaming a file.
 */
void WindowClass::renameFilePopup()
{

}

/**
 * @brief Displays a popup for deleting a file.
 */
void WindowClass::deleteFilePopup()
{

}

/**
 * @brief Renames a file.
 * 
 * @param old_path The current path of the file.
 * @param new_path The new path for the file.
 * @return true if the file was successfully renamed, false otherwise.
 */
bool WindowClass::renameFile(const fs::path &old_path, const fs::path &new_path)
{

}

/**
 * @brief Deletes a file.
 * 
 * @param path The path of the file to delete.
 * @return true if the file was successfully deleted, false otherwise.
 */
bool WindowClass::deleteFile(const fs::path &path)
{

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
    window_obj.Draw("File Explorer Tool");
}
