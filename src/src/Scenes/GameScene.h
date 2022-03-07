/*
 * GameSceen.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Jordan Hunt
 */

#ifndef SCENES_GAMESCENE_H_
#define SCENES_GAMESCENE_H_

#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene : public Scene
{
public:
    GameScene();
    virtual ~GameScene();
    GameScene(std::unique_ptr<Game> gamePointer);
    virtual void Initialize() override;
    virtual void Update(uint32_t deltaTime) override;
    virtual void Render(Screen &screen) override;
    virtual const std::string &GetSceneName() const override;

private:
    std::unique_ptr<Game> game;
};

#endif /* SCENES_GAMESCENE_H_ */
