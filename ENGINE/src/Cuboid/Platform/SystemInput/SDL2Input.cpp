//
// Created by tawanda on 14/2/2021.
//

#include "SDL2Input.h"

bool Cuboid::SDL2Input::IsKeyPressedImpl(Cuboid::KeyCode key) {
    return false;
}

bool Cuboid::SDL2Input::IsMouseButtonPressedImpl(Cuboid::MouseCode button) {
    return false;
}

std::pair<float, float> Cuboid::SDL2Input::GetMousePositionImpl() {
    return std::pair<float, float>();
}

float Cuboid::SDL2Input::GetMouseXImpl() {
    return 0;
}

float Cuboid::SDL2Input::GetMouseYImpl() {
    return 0;
}
