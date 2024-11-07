#pragma once

#include <cstdint>
#include <string_view>
#include <filesystem>

namespace fs = std::filesystem;

class WindowClass
{
public:
    WindowClass()
        : currentPath(fs::current_path()), selectedEntry(fs::path{}){};
    void Draw(std::string_view label);

private:
    void DrawMenu(void);
    void DrawContent(void);
    void DrawActions(void);
    void DrawFilter(void);

    void OpenFileWithDefaultEditor(void);
    void RenameFilePopup(void);
    bool RenameFile(const fs::path &old_path, const fs::path &new_path);
    void DeleteFilePopup(void);
    bool DeleteFile(const fs::path &path);

private:
    fs::path currentPath;
    fs::path selectedEntry;
    bool renameDialogOpen = false;
    bool deleteDialogOpen = false;
};

void render(WindowClass &window_obj);
