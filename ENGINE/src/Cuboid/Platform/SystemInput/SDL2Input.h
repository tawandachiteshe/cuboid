//
// Created by tawanda on 14/2/2021.
//

#ifndef CUBOID_SDL2INPUT_H
#define CUBOID_SDL2INPUT_H

#include "Cuboid/Core/Input.h"

namespace Cuboid {

    class SDL2Input : public Input {
    protected:
        bool IsKeyPressedImpl(KeyCode key) override;

        bool IsMouseButtonPressedImpl(MouseCode button) override;

        std::pair<float, float> GetMousePositionImpl() override;

        float GetMouseXImpl() override;

        float GetMouseYImpl() override;

    };

}

#endif //CUBOID_SDL2INPUT_H
