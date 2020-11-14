#ifndef WAVE_CANNON_HPP
#define WAVE_CANNON_HPP

struct WaveCannon {
    enum class Status {
        Inactive,
        Charging,
        Firing,
    };
    Status status = Status::Inactive;
    unsigned complete_charge_point = 3000;
    unsigned charging_ticks = 0;
};

#endif
