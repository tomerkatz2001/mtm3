#ifndef SOLDIER_H
#define SOLDIER_H
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm{
static const units_t SOLDIRE_MAX_MOVE=5;
static const units_t SOLDIRE_RELOAD=3;
static const units_t SOLDIRE_ATTACK_COST=1;
class Soldire : public Character{

    public:
    ~Soldire()=default;
    Soldire(Team team, units_t health, units_t ammo, units_t range, units_t power);
    void makePure() override{};
    Soldire(const Soldire& Soldire)=default;
    Soldire& operator=(const Soldire& soldire)=default;
    char printType()override;
    void lowerAmmo(units_t how_much)override;


};



}


#endif