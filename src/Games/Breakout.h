/*
 * Breakout.h
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_
#include "Game.h"
class Breakout : public Game
{
public:
    Breakout();
    virtual ~Breakout();
    virtual void Update(uint32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() const override;
    virtual void Initialize(GameController &gameController) const override;
};

#endif /* GAMES_BREAKOUT_H_ */
