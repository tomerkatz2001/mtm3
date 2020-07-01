#ifndef SNIPER_H
#define SNIPER_H
#include"Auxiliaries.h"
#include"Character.h"
namespace mtm
{
static const units_t SNIPER_MAX_MOVE=4;
static const units_t SNIPER_RELOAD=2;
static const units_t SNIPER_ATTACK_COST=1;
static const int SNIPER_SEQUENCE=3;
class Sniper : public Character{
    

    public:
    int sequence;
    ~Sniper()=default;
    Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);
    void makePure() override{};
    Sniper(const Sniper& sniper)=default;
    Sniper& operator=(const Sniper& sniper)=default;
    char printType()override;
    void lowerAmmo(units_t how_much)override;


};  





} 
#endif