/*
 * GameScene.cpp
 *
 *  Created on: Jan 28, 2022
 *      Author: Jordan Hunt
 */
#include <GameScene.h>
GameScene::GameScene()
{
    // TODO Auto-generated constructor stub
}
GameScene::~GameScene()
{
    // TODO Auto-generated destructor stub
}
GameScene::GameScene(std::unique_ptr<Game> gamePointer) : game(std::move(gamePointer))
{
}
void GameScene::Initialize()
{
    game->Initialize(gameController);
}
void GameScene::Update(uint32_t deltaTime)
{
    game->Update(deltaTime);
}
void GameScene::Render(Screen &screen)
{
    game->Draw(screen);
}
const std::string &GameScene::GetSceneName() const
{
    static std::string sceneName = "";
    return sceneName;
}
