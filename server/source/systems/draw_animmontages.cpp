#include "components/AnimMontage.hpp"
#include "components/Destructible.hpp"
#include "Modules.hpp"
#include <iostream>

void draw_animmontages
(IDisplayModule &display, const Transform &transform, AnimMontage &montage)
{
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    montage.update();
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    unsigned current = montage.ticksCount / montage.duration;
    display.drawSprite(montage.spritesheet, transform, montage.ids.at(current));
    montage.ticksCount++;
}

void draw_deathmontages
(IDisplayModule &display, const Transform &transform, DeathMontage &montage)
{
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    montage.update();
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    unsigned current = montage.ticksCount / montage.duration;
    display.drawSprite(montage.spritesheet, transform, montage.ids.at(current));
    montage.ticksCount++;
}

void play_deathmontages(Destructible &destructible, DeathMontage &montage)
{
    if (montage.getStatus() == AnimMontage::Status::Inactive \
&& destructible.status == Destructible::Status::Dying) {
        montage.play();
        std::cout << "playing death montage\n";
    }
    if (montage.getStatus() == AnimMontage::Status::Terminated) {
        std::cout << "Terminated\n";
        destructible.status = Destructible::Status::Dead;
    }
}
