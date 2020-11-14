#ifndef ANIM_MONTAGE_HPP
#define ANIM_MONTAGE_HPP

#include <string>
#include <vector>

class AnimMontage {
public:
    enum class Status {
        Inactive,
        Playing,
        Paused,
        Terminated,
    };
protected:
    Status m_status;
public:
    std::string spritesheet;
    std::vector<unsigned> ids;
    unsigned duration;
    unsigned ticksCount;
    AnimMontage(const std::string &_spritesheet, std::vector<unsigned> _ids, unsigned _duration);
    void play();
    void pause();
    void update();
    Status getStatus() const;
};

class DeathMontage : public AnimMontage {};

#endif
