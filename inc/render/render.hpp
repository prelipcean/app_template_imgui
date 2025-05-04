#pragma once

#include <cstdint>
#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Class representing a window or rendering context.
 * 
 * This class provides methods for rendering UI elements and managing
 * file operations such as renaming and deleting files. It also maintains
 * the current and selected file paths for operations.
 */
class WindowClass
{
public:
    /**
     * @brief Constructor to initialize the window class.
     * 
     * Initializes the current path to the current working directory.
     */
    WindowClass();

    /**
     * @brief Destructor to clean up resources.
     * 
     * Ensures that any resources associated with the window or rendering context
     * are properly released.
     */
    ~WindowClass();

    /**
     * @brief Draws a UI element with the specified label.
     * 
     * This method is responsible for rendering a UI element with the given label.
     * It is typically called during the rendering loop.
     * 
     * @param label The label to display for the UI element.
     */
    void Draw(std::string_view label);

    WindowClass(const WindowClass &) = delete;            // Disable copy constructor
    WindowClass &operator=(const WindowClass &) = delete; // Disable copy assignment
    WindowClass(WindowClass &&) = default;               // Enable move constructor
    WindowClass &operator=(WindowClass &&) = default;    // Enable move assignment

private:
    /**
     * @brief Draws the menu section of the UI.
     * 
     * This method is responsible for rendering the menu bar or menu-related UI elements.
     */
    void DrawMenu();

    /**
     * @brief Draws the main content section of the UI.
     * 
     * This method handles rendering the primary content area of the application.
     */
    void DrawContent();

    /**
     * @brief Draws the actions section of the UI.
     * 
     * This method is used to render UI elements related to user actions, such as buttons.
     */
    void DrawActions();

    /**
     * @brief Draws the filter section of the UI.
     * 
     * This method is responsible for rendering UI elements that allow users to filter content.
     */
    void DrawFilter();

    /**
     * @brief Opens the selected file with the default editor.
     * 
     * This method launches the default application associated with the selected file.
     */
    void openFileWithDefaultEditor();

    /**
     * @brief Displays a popup for renaming a file.
     * 
     * This method shows a UI popup that allows the user to rename the selected file.
     */
    void renameFilePopup();

    /**
     * @brief Displays a popup for deleting a file.
     * 
     * This method shows a UI popup that allows the user to confirm the deletion of the selected file.
     */
    void deleteFilePopup();

    /**
     * @brief Renames a file.
     * 
     * This method renames a file from the specified old path to the new path.
     * 
     * @param old_path The current path of the file.
     * @param new_path The new path for the file.
     * @return true if the file was successfully renamed, false otherwise.
     */
    bool renameFile(const fs::path &old_path, const fs::path &new_path);

    /**
     * @brief Deletes a file.
     * 
     * This method deletes the file at the specified path.
     * 
     * @param path The path of the file to delete.
     * @return true if the file was successfully deleted, false otherwise.
     */
    bool deleteFile(const fs::path &path);

private:
    fs::path currentPath; ///< The current directory path being displayed or managed.
    fs::path selectedEntry; ///< The currently selected file or directory.

    bool renameDialogOpen = false; ///< Flag indicating if the rename dialog is open.
    bool deleteDialogOpen = false; ///< Flag indicating if the delete dialog is open.
};

/**
 * @brief Renders the UI using the provided WindowClass object.
 * 
 * This function is responsible for invoking the rendering logic of the
 * `WindowClass` object. It is typically called during the main rendering loop.
 * 
 * @param window_obj Reference to a WindowClass object used for rendering.
 */
void render(WindowClass &window_obj);
