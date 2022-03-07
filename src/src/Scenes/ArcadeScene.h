/*
 * ArcadeScene.h
 *
 *  Created on: Jan 12, 2022
 *      Author: Jordan Hunt
 */

#ifndef SCENES_ARCADESCENE_H_
#define SCENES_ARCADESCENE_H_
#include "Scene.h"
#include <memory>
#include "Screen.h"
#include "Triangle.h"
#include "Circle.h"
#include "AxisAlignedRectangle.h"
#include "Color.h"
#include "GameController.h"
#include <iostream>
// Forward Declare
class Screen;
enum GameList
{
    TETRIS, BREAK_OUT, ASTEROIDS, HAKMAN, NUMBER_OF_GAMES
};
class ArcadeScene: public Scene
{
public:
    ArcadeScene();
    virtual ~ArcadeScene();
    virtual void Initialize() override;
    virtual void Update(uint32_t deltaTime) override;
    virtual void Render(Screen &theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    std::unique_ptr<Scene> GetScene(GameList game);
};
#endif /* SCENES_ARCADESCENE_H_ */
