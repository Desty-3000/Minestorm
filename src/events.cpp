
#include "events.h"

#include <iostream>

#include "player.h"
#include "game_engine.h"

void playerOneInputs(GameEngine* engine)
{
    if (IsKeyDown(P1_FORWARD))
    {
        engine->m_playerOnePtr->m_spaceShip->addVelocity(.2f);
        engine->m_playerOnePtr->m_spaceShip->calculateDirection();
    }
    if (IsKeyPressed(P1_TELEPORT) || IsKeyPressed(P1_TELEPORT_BIS))
    {
        engine->m_playerOnePtr->m_spaceShip->teleport();
    }
    if (IsKeyDown(P1_LEFT))
    {
        engine->m_playerOnePtr->m_spaceShip->m_angle -= 1.f * GetFrameTime();
    }
    if (IsKeyDown(P1_RIGHT))
    {
        engine->m_playerOnePtr->m_spaceShip->m_angle += 1.f * GetFrameTime();
    }
    if (IsKeyPressed(P1_SHOOT))
    {
        engine->m_playerOnePtr->shoot();
    }
};

void playerTwoInputs(GameEngine* engine)
{
    if (IsKeyPressed(P2_SHOOT))
    {
        engine->m_playerTwoPtr->shoot();
    }
    if (IsKeyPressed(P2_TELEPORT) || IsKeyPressed(P2_TELEPORT_BIS))
    {
        engine->m_playerTwoPtr->m_spaceShip->teleport();
    }
    if (IsKeyDown(P2_FORWARD))
    {
        engine->m_playerTwoPtr->m_spaceShip->addVelocity(.2f);
        engine->m_playerTwoPtr->m_spaceShip->calculateDirection();
    }
    if (IsKeyDown(P2_LEFT))
    {
        engine->m_playerTwoPtr->m_spaceShip->m_angle -= 1.f * GetFrameTime();
    }
    if (IsKeyDown(P2_RIGHT))
    {
        engine->m_playerTwoPtr->m_spaceShip->m_angle += 1.f * GetFrameTime();
    }
}

void gameInputs(GameEngine* engine)
{
    //disable Escape Shutdown shortcut 
    SetExitKey(0);

    if (engine->m_gameState == GameState::GAMEOVER || engine->m_gameState == GameState::PAUSE)
    {

        if (IsKeyPressed(GAME_OVER_TO_MAIN))
        {
            engine->m_gameState = GameState::MAIN;
            engine->resetStats();
        }
    }
    if (engine->m_gameState == GameState::MAIN)
    {
        SetExitKey(GAME_OVER_TO_MAIN);
        if (IsKeyPressed(GAME_START_SOLO))
        {
            engine->startGame(GameType::SINGLEPLAYER);
        }
        else if (IsKeyPressed(GAME_START_COOP))
        {
            engine->startGame(GameType::COOP);
        }
    }
    else 
    {
        if (IsKeyPressed(GAME_PAUSE))
        {
            toggleGameState(engine->m_gameState);
        }
        if (IsKeyPressed(GAME_DEBUG))
        {
            toggleBool(engine->m_isDebugOn);
        }
    }
}


void handleEvents(GameEngine* engine)
{
    if (engine->m_gameState == GameState::PLAYING && engine->m_has_wave_started)
    {
        if (engine->m_playerOnePtr != nullptr)
            playerOneInputs(engine);
        if (engine->m_gameType == GameType::COOP && engine->m_playerTwoPtr != nullptr)
            playerTwoInputs(engine);
    }
        gameInputs(engine);
}
