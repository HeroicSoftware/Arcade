/*
 * Application.cpp
 *
 *  Created on: Jan 9, 2022
 *      Author: Jordan Hunt
 */
#include "Application.h"
#include "ArcadeScene.h"
// Create one instance of the application using Singleton Design Pattern. Only use the singleton throughout the program.
Application &Application::Singleton()
{
    static Application theApplication;
    return theApplication;
}
bool Application::Initialize(uint32_t width, uint32_t height, uint32_t magnification)
{
    applicationWindow = applicationScreen.Initialize(width, height, magnification);
    // Arcade Scene
    std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
    PushScene(std::move(arcadeScene));
    return (applicationWindow != nullptr);
}
void Application::Run()
{
    if (this->applicationWindow)
    {
        Line2D line2D =
            {Vector2D(0, 0), Vector2D(applicationScreen.GetWidth(), applicationScreen.GetHeight())};
        Line2D line2D2 =
            {Vector2D(applicationScreen.GetWidth(), 0), Vector2D(0, applicationScreen.GetHeight())};
        Triangle testTriangle =
            {Vector2D(60, 10), Vector2D(10, 110), Vector2D(110, 110)};
        AxisAlignedRectangle testRectangle =
            {Vector2D(applicationScreen.GetWidth() / 2 - 25, applicationScreen.GetHeight() / 2 - 25), 50, 50};
        Circle testCircle =
            {Vector2D(applicationScreen.GetWidth() / 2 + 50, applicationScreen.GetHeight() / 2 + 50), 50};
        testTriangle.MoveTo(Vector2D((applicationScreen.GetWidth() / 2), (applicationScreen.GetHeight() / 2)));
        // Draw two lines that will cross as the center of the screen.
        applicationScreen.Draw(line2D, Color::Red());
        applicationScreen.Draw(line2D2, Color::Red());
        // Draw the triangle at the new destination
        bool isRunning = true;
        // Get Current Time - milliseconds
        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        // Ten milliseconds - update scene in 10 millisecond intervals
        uint32_t deltaTime = 10;
        uint32_t accumulatorTime = 0;
        // Start the input controller
        applicationInputController.Initialize([&isRunning](uint32_t deltaTime, InputState state)
                                              { isRunning = false; });

        while (isRunning == true)
        {
            // Time
            currentTick = SDL_GetTicks();
            uint32_t frameTime = currentTick - lastTick;
            // Cap frameTime
            if (frameTime > 300)
            {
                frameTime = 300;
            }
            lastTick = currentTick;
            accumulatorTime += frameTime;
            /*
             * =========
             * Game Loop
             * =========
             */
            // Input
            applicationInputController.Update(deltaTime);
            // Get the top scene
            Scene *currentScene = Application::PeekScene();
            assert(currentScene && "[FAILED ASSERTION] - No scene available");
            if (currentScene)
            {
                // Update
                while (accumulatorTime >= deltaTime)
                {
                    currentScene->Update(deltaTime);
                    // Update current scene by deltaTime
                    // std::cout << "Delta Time Step in milliseconds: [" << deltaTime << "]" << std::endl;
                    accumulatorTime -= deltaTime;
                }
                // Render
                currentScene->Render(applicationScreen);
            }
            applicationScreen.SwapScreen();
        }
    }
}
void Application::PushScene(std::unique_ptr<Scene> scene)
{
    assert(scene && "[FAILED ASSERTION] - Do not push nullptr");
    if (scene)
    {
        // Initialize the when it is pushed to the stack.
        scene->Initialize();
        // Reset input for each scene
        applicationInputController.SetGameController(scene->GetGameController());
        sceneStack.emplace_back(std::move(scene));
        SDL_SetWindowTitle(applicationWindow, PeekScene()->GetSceneName().c_str());
    }
}
void Application::PopScene()
{
    if (sceneStack.size() > 1)
    {
        sceneStack.pop_back();
    }
    if (PeekScene())
    {
        // Return the last scene in the stack which is the top
        applicationInputController.SetGameController(PeekScene()->GetGameController());
        SDL_SetWindowTitle(applicationWindow, PeekScene()->GetSceneName().c_str());
    }
}
// Return the last scene in the stack which is the top
Scene *Application::PeekScene()
{
    if (sceneStack.empty())
    {
        return nullptr;
    }
    else
    {
        // Return the last scene in the stack which is the top
        return sceneStack.back().get();
    }
}
