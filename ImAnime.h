#pragma once
#include <math.h>

namespace ImAnime {

    // Define a struct to hold information about the animation
    struct Animation {
        bool isVisible = false; // Visibility flag
        float progress = 0.0f; // Animation progress
        float duration = 1.0f; // Animation duration
    };

    // Enum class for animation types
    enum class AnimationType {
        CubicBezier,
        Linear,
        EaseInOut
    };

    // Enum class for slide directions
    enum class SlideDirection {
        ToLeft,
        ToRight,
        ToTop,
        ToBottom
    };

    // Function to perform cubic bezier interpolation
    float cubicBezier(float t, float p0, float p1, float p2, float p3) {
        float u = 1.0f - t;
        float tt = t * t;
        float uu = u * u;
        float uuu = uu * u;
        float ttt = tt * t;

        float res = uuu * p0; // (1-t)^3 * P0
        res += 3 * uu * t * p1; // 3 * (1-t)^2 * t * P1
        res += 3 * u * tt * p2; // 3 * (1-t) * t^2 * P2
        res += ttt * p3; // t^3 * P3

        return res;
    }

    // Function to perform ease-in-out interpolation
    float easeInOut(float t) {
        return t < 0.5f ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
    }

    // Function to animate any ImGui element with slide and fade animation
    template<typename DrawElement>
    void animateElement(Animation& animation, float slideOffset, float fadeOffset, float duration, DrawElement drawFunc, AnimationType animType = AnimationType::CubicBezier, SlideDirection slideDir = SlideDirection::ToLeft) {
        if (animation.isVisible) {
            animation.progress += ImGui::GetIO().DeltaTime / duration;
            if (animation.progress >= 1.0f) {
                animation.progress = 1.0f;
            }

            float offset;
            switch (slideDir) {
            case SlideDirection::ToLeft:
                offset = -slideOffset;
                break;
            case SlideDirection::ToRight:
                offset = slideOffset;
                break;
            case SlideDirection::ToTop:
                offset = -slideOffset;
                break;
            case SlideDirection::ToBottom:
                offset = slideOffset;
                break;
            }

            switch (animType) {
            case AnimationType::CubicBezier:
                // Use cubic bezier interpolation for smoother animation
                offset *= cubicBezier(animation.progress, 0.0f, 0.42f, 0.58f, 1.0f);
                break;
            case AnimationType::Linear:
                // Linear interpolation
                offset *= animation.progress;
                break;
            case AnimationType::EaseInOut:
                // Use ease-in-out interpolation
                offset *= easeInOut(animation.progress);
                break;
            }

            float alpha;
            if (animType == AnimationType::CubicBezier || animType == AnimationType::EaseInOut) {
                alpha = cubicBezier(animation.progress, 0.0f, 0.42f, 0.58f, 1.0f) * fadeOffset;
            }
            else {
                alpha = animation.progress * fadeOffset;
            }

            // Apply slide and fade effects
            if (slideDir == SlideDirection::ToLeft || slideDir == SlideDirection::ToRight) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
            }
            else {
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset);
            }
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);

            // Call the draw function provided by the user
            drawFunc();

            // Restore default alpha
            ImGui::PopStyleVar();

        }
    }

} // namespace ImAnime
