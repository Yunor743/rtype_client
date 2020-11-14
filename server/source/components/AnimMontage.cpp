#include "components/AnimMontage.hpp"

AnimMontage::AnimMontage(const std::string &_spritesheet, std::vector<unsigned> _ids, unsigned _duration)
: ticksCount(0), spritesheet(_spritesheet), ids(_ids), duration(_duration), m_status(AnimMontage::Status::Inactive)
{}

void AnimMontage::play()
{
    m_status = Status::Playing;
}

void AnimMontage::pause()
{
    m_status = Status::Paused;
}

AnimMontage::Status AnimMontage::getStatus() const
{
    return m_status;
}

void AnimMontage::update()
{
    if (ticksCount >= duration * ids.size())
        m_status = Status::Terminated;
}
