#pragma once

#include <cstdint>
#include <string_view>

// Class representing a window or rendering context
class WindowClass
{
public:
    /**
     * @brief Draws a UI element with the specified label.
     * 
     * @param label The label to display for the UI element.
     */
    void Draw(std::string_view label);

    /**
     * @brief Destructor to clean up resources.
     */
    ~WindowClass();
};

/**
 * @brief Renders the UI using the provided WindowClass object.
 * 
 * @param window_obj Reference to a WindowClass object used for rendering.
 */
void render(WindowClass &window_obj);
