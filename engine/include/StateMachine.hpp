#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stack>
#include <memory>
#include <optional>
#include <vector>
#include <functional>

class Game;

class AState {
private:
    short m_id;
    static short m_stateCount;
public:
    AState();
    ~AState();
    short getId();
    virtual void onStart(Game &instance) = 0;
    virtual void onPause(Game &instance) = 0;
    virtual void onResume(Game &instance) = 0;
    virtual void onTick(Game &instance) = 0;
    virtual void onStop(Game &instance) = 0;
};

class StateMachine {
private:
    Game &m_instance;
    std::stack<std::unique_ptr<AState>> m_statesStack;
public:
    StateMachine(Game &instance);
    void setState(std::unique_ptr<AState> state);
    void stackState(std::unique_ptr<AState> state);
    std::optional<std::reference_wrapper<AState>> getCurrentState() const;
    void leaveCurrentState();
    void update();
};

#endif
