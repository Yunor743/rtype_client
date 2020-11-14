#include "states/DebugState.hpp"
#include "Game.hpp"
#include <iostream>

DebugState::DebugState() : m_tickCounter(0), AState()
{}

void DebugState::onStart(Game &instance)
{
    std::cout << "[" << getId() << "] Started !\n";
}

void DebugState::onPause(Game &instance)
{
    std::cout << "[" << getId() << "] Paused !\n";
}

void DebugState::onResume(Game &instance)
{
    std::cout << "[" << getId() << "] Resumed !\n";
}

void DebugState::onTick(Game &instance)
{
    std::cout << "[" << getId() << "] Ticked !\n";
    if (m_tickCounter == 5 && getId() == 0) {
        std::cout << "[" << getId() << "] I'm dying.., 2 pls take my place now\n";
        std::unique_ptr<AState> state2(new DebugState);
        instance.stateMachine.setState(std::move(state2));
    }
    if (m_tickCounter == 2 && getId() == 0) {
        std::cout << "[" << getId() << "] Okay 1, take my place for a few turns please !\n";
        std::unique_ptr<AState> state1(new DebugState);
        instance.stateMachine.stackState(std::move(state1));
    }
    if (m_tickCounter == 2 && getId() == 1) {
        std::cout << "[" << getId() << "] I'm dying..., take your turn back 0 !\n";
        instance.stateMachine.leaveCurrentState();
    }
    if (m_tickCounter == 2 && getId() == 2) {
        std::cout << "[" << getId() << "] I'm dying too... this is the end of it all...\n";
        instance.stateMachine.leaveCurrentState();
    }
    m_tickCounter++;
}

void DebugState::onStop(Game &instance)
{
    std::cout << "[" << getId() << "] Stopped !\n";
}
