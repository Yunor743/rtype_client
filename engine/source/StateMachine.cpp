#include "StateMachine.hpp"
#include "Game.hpp"

short AState::m_stateCount = 0;

// AState methods

AState::AState() : m_id(AState::m_stateCount++)
{}

AState::~AState()
{}

short AState::getId()
{
    return m_id;
}

// StateMachine methods

StateMachine::StateMachine(Game &instance) : m_instance(instance)
{}

void StateMachine::setState(std::unique_ptr<AState> state)
{
    leaveCurrentState();
    stackState(std::move(state));
}

void StateMachine::stackState(std::unique_ptr<AState> state)
{
    if (getCurrentState())
        (*getCurrentState()).get().onPause(m_instance);
    m_statesStack.push(std::move(state));
    m_statesStack.top()->onStart(m_instance);
}

std::optional<std::reference_wrapper<AState>> StateMachine::getCurrentState() const
{
    if (!m_statesStack.empty())
        return *(m_statesStack.top());
    return {};
}

void StateMachine::leaveCurrentState()
{
    if (!m_statesStack.empty()) {
        (*getCurrentState()).get().onStop(m_instance);
        m_statesStack.pop();
    }
    if (getCurrentState())
        (*getCurrentState()).get().onResume(m_instance);
}

void StateMachine::update()
{
    if (getCurrentState())
        (*getCurrentState()).get().onTick(m_instance);
}
