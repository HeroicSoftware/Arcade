/*
 * Scene.h
 *
 *  Created on: Jan 12, 2022
 *      Author: Jordan Hunt
 */

#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_
#include <string>
#include <stdint.h>
#include "GameController.h"

class Screen;

// Interface - Pure Virtual functions, base of all scenes in the application
class Scene
{
public:
    Scene();
    virtual ~Scene();
    virtual void Initialize() = 0;
    virtual void Update(uint32_t deltaTime) = 0;
    virtual void Render(Screen &theScreen) = 0;
    virtual const std::string &GetSceneName() const = 0;
    inline GameController *GetGameController()
    {
        return &gameController;
    }

protected:
    GameController gameController;
};

#endif /* SCENES_SCENE_H_ */
