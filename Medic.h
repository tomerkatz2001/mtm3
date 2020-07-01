#ifndef MEDIC_H
#define MEDIC_H
#include"Auxiliaries.h"
#include "Character.h"
namespace mtm{

static const units_t MEDIC_MAX_MOVE=5;
static const units_t MEDIC_RELOAD=5;
static const units_t MEDIC_ATTACK_COST=1;
class Medic: public Character
{
    public:
    ~Medic()=default;
    Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
    void makePure() override{};
    Medic(const Medic& medic)=default;
    Medic& operator=(const Medic& medic)=default;
    char printType()override;
    void lowerAmmo(units_t how_much)override;
};

}
#endif