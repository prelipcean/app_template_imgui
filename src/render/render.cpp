#include <iostream> // For debugging or logging (if needed)
#include "fmt/format.h" // For formatted output (if used elsewhere)
#include "imgui.h" // Dear ImGui library
#include "implot.h" // ImPlot library

#include "render.hpp" // Header file for WindowClass and render function

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // For file logging


/**
 * @brief Constructor for the WindowClass.
 * 
 * Initializes the current path to the current working directory.
 */
WindowClass::WindowClass() : currentPath(fs::current_path()), selectedEntry(fs::path{}) 
{
    // Ensure the logs directory exists
    try
    {
        fs::create_directories("logs");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to create logs directory: " << e.what() << std::endl;
    }

    // Initialize spdlog with a file sink
    try
    {
        if (!spdlog::get("file_logger"))
        {
            static auto logger = spdlog::basic_logger_mt("file_logger", "logs/application.log");
            spdlog::set_default_logger(logger);
            spdlog::set_level(spdlog::level::info); // Set log level to info
        }
        spdlog::info("Logger initialized successfully.");
    }
    catch (const spdlog::spdlog_ex &e)
    {
        std::cerr << "Failed to initialize file logger: " << e.what() << std::endl;
    }

    // Log the initialization message
    spdlog::info("WindowClass initialized with current path: {}", currentPath.string());
    //std::cout << "WindowClass initialized with current path: " << currentPath << std::endl;
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
    spdlog::info("WindowClass destructor called. Resources cleaned up.");

    //std::cout << "WindowClass destructor called. Resources cleaned up." << std::endl;
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
    for (const auto &entry : fs::directory_iterator(currentPath))
    {
        const auto is_selected = entry.path() == selectedEntry;
        const auto is_directory = entry.is_directory();
        const auto is_file = entry.is_regular_file();
        auto entry_name = entry.path().filename().string();

        if (is_directory)
            entry_name = "[D]" + entry_name;
        else if (is_file)
            entry_name = "[F]" + entry_name;

        if (ImGui::Selectable(entry_name.c_str(), is_selected))
        {
            if (is_directory)
                currentPath /= entry.path().filename();

            selectedEntry = entry.path();
        }
    }
}

/**
 * @brief Draws the actions section of the UI.
 * 
 * Displays actions (e.g., Open, Rename, Delete) for the selected file or directory.
 */
void WindowClass::DrawActions()
{
    if (fs::is_directory(selectedEntry))
        ImGui::Text("Selected dir: %s", selectedEntry.string().c_str());
    else if (fs::is_regular_file(selectedEntry))
        ImGui::Text("Selected file: %s", selectedEntry.string().c_str());
    else
    {
        ImGui::Text("Selected file: n/a");
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.0f);
        ImGui::Button("Non-clickable button");
        ImGui::PopStyleVar();
        return;
    }

    if (fs::is_regular_file(selectedEntry) && ImGui::Button("Open"))
        openFileWithDefaultEditor();

    ImGui::SameLine();

    if (ImGui::Button("Rename"))
    {
        renameDialogOpen = true;
        ImGui::OpenPopup("Rename File");
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete"))
    {
        deleteDialogOpen = true;
        ImGui::OpenPopup("Delete File");
    }

    renameFilePopup();
    deleteFilePopup();
}

/**
 * @brief Draws the filter section of the UI.
 * 
 * Allows filtering files by extension and displays the count of matching files.
 */
void WindowClass::DrawFilter()
{
    static char extension_filter[16] = {"\0"};

    ImGui::Text("Filter by extension");
    ImGui::SameLine();
    ImGui::InputText("###inFilter", extension_filter, sizeof(extension_filter));

    if (std::strlen(extension_filter) == 0)
        return;

    auto filtered_file_count = std::size_t{0};
    for (const auto &entry : fs::directory_iterator(currentPath))
    {
        if (!fs::is_regular_file(entry))
            continue;

        if (entry.path().extension().string() == extension_filter)
            ++filtered_file_count;
    }

    ImGui::Text("Number of files: %u", filtered_file_count);
}

/**
 * @brief Opens the selected file with the default editor.
 */
void WindowClass::openFileWithDefaultEditor()
{
    #ifdef _WIN32
    const auto command = "start \"\" \"" + selectedEntry.string() + "\"";
#elif __APPLE__
    const auto command = "open \"" + selectedEntry.string() + "\"";
#else
    const auto command = "xdg-open \"" + selectedEntry.string() + "\"";
#endif

    std::system(command.c_str());
}

/**
 * @brief Displays a popup for renaming a file.
 */
void WindowClass::renameFilePopup()
{
    if (ImGui::BeginPopupModal("Rename File", &renameDialogOpen))
    {
        static char buffer_name[512] = {'\0'};

        ImGui::Text("New name: ");
        ImGui::InputText("###newName", buffer_name, sizeof(buffer_name));

        if (ImGui::Button("Rename"))
        {
            auto new_path = selectedEntry.parent_path() / buffer_name;
            if (renameFile(selectedEntry, new_path))
            {
                renameDialogOpen = false;
                selectedEntry = new_path;
                std::memset(buffer_name, 0, sizeof(buffer_name));
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel"))
            renameDialogOpen = false;

        ImGui::EndPopup();
    }
}

/**
 * @brief Displays a popup for deleting a file.
 */
void WindowClass::deleteFilePopup()
{
    if (ImGui::BeginPopupModal("Delete File", &deleteDialogOpen))
    {
        ImGui::Text("Are you sure you want to delete %s?",
                    selectedEntry.filename().string().c_str());

        if (ImGui::Button("Yes"))
        {
            if (deleteFile(selectedEntry))
                selectedEntry.clear();
            deleteDialogOpen = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("No"))
            deleteDialogOpen = false;

        ImGui::EndPopup();
    }
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
    try
    {
        fs::rename(old_path, new_path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

/**
 * @brief Deletes a file.
 * 
 * @param path The path of the file to delete.
 * @return true if the file was successfully deleted, false otherwise.
 */
bool WindowClass::deleteFile(const fs::path &path)
{
    try
    {
        fs::remove(path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
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
