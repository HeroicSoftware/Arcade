/*
 * Game.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_GAME_H_
#define GAMES_GAME_H_
#include <string>
#include <GameController.h>
#include <Scene.h>

class Game
{
public:
    Game();
    virtual ~Game();
    virtual void Update(uint32_t deltaTime) = 0;
    virtual void Draw(Screen &screen) = 0;
    virtual const std::string &GetName() const = 0;
    virtual void Initialize(GameController &gameController) = 0;
};

#endif /* GAMES_GAME_H_ */
