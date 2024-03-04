# ImAnime 

ImAnime is a lightweight C++ header-only library that provides easy-to-use functions for animating ImGui elements with various animation types including cubic bezier, linear, and ease-in-out. It allows developers to create smooth animations for their ImGui-based user interfaces effortlessly.


1. **Installation:**
   - Simply include the `imanime.h` header file in your project to start using ImAnime.

2. **Usage:**
   - Include the necessary ImGui and ImAnime headers in your source file.
   - Create an `Animation` struct to hold animation information.
   - Use the `animateElement` function to animate ImGui elements with specified animation type, duration, offsets, and slide directions.
   - Choose from animation types: `CubicBezier`, `Linear`, or `EaseInOut`, and slide directions: `ToLeft`, `ToRight`, `ToTop`, `ToBottom`.
   - Example usage:
 ```cpp
 #include "imgui.h"
 #include "imanime.h"

ImAnime::Animation animation;

while (!done) {
    ImGui::Begin("Hello, World");
    {
        // Check if the element should be visible
        if (!animation.isVisible) {
            animation.isVisible = true; // Set visibility to true to trigger the animation
        }
        
        // Render the animated element with ease-in-out animation, sliding from left
        ImAnime::animateElement(animation, 30.0f, 1.0f, 0.5f, [](){

            ImGui::Text("Animated Text");

        }, ImAnime::AnimationType::EaseInOut, ImAnime::SlideDirection::ToBottom);  
        // Pass AnimationType::EaseInOut and SlideDirection::ToBottom
    }
    ImGui::End();
}
```

3. **Mimicking CSS Animations:**
   - ImAnime provides functionality to mimic animations commonly seen in CSS-based websites. With slide directions like `ToLeft`, `ToRight`, `ToTop`, and `ToBottom`, developers can replicate CSS animations in their ImGui-based user interfaces. Combined with animation types such as cubic bezier, linear, or ease-in-out, ImAnime enables the creation of smooth and visually appealing animations similar to those found in web development.

4. **Contributing:**
   - Contributions are welcome! Feel free to open an issue for bug reports, feature requests, or submit a pull request for improvements.

5. **License:**
   - ImAnime is licensed under the MIT License. See the LICENSE file for more details.
