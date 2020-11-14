#include "components/PlayerShipController.hpp"

PlayerShipController::PlayerShipController(unsigned player_id, float speed)
 : m_player_id(player_id), m_speed(speed),
    moovingUp(false), moovingDown(false), moovingLeft(false), moovingRight(false),
    firing(false)
{}

unsigned PlayerShipController::getPlayerId() const
{
    return m_player_id;
}

float PlayerShipController::getSpeed() const
{
    return m_speed;
}
