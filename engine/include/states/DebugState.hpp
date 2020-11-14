#ifndef DEBUG_STATE_HPP
#define DEBUG_STATE_HPP

#include "StateMachine.hpp"

class DebugState : public AState {
    int m_tickCounter;
public:
    DebugState();
private:
    void onStart(Game &instance) override;
    void onPause(Game &instance) override;
    void onResume(Game &instance) override;
    void onTick(Game &instance) override;
    void onStop(Game &instance) override;
};


#endif
