#ifndef CHARACTER_H
#define CHARACTER_H
#include "Auxiliaries.h" 
namespace mtm{

class Character
{
    protected:
    units_t health;
    units_t ammo;
    const units_t range;
    const units_t power;
    Team team;
    units_t attack_cost;//how much ammo is being used in an attack
    units_t max_move;//how much tiles the character can move
    units_t recharge_ammo;//how much ammo is added in one recharge
    
    
    public:
    Character(Team team, units_t health, units_t ammo, units_t range, units_t power);
    int sequence=0;
    units_t getAttackCost() const;
    units_t getMaxMove() const;
    void rechargeAmmo();
    units_t getHealth()const;
    units_t getAmmo()const;
    units_t getRange()const;
    units_t getPower()const;
    Team getTeam()const;
    void lowerHealth(units_t how_much);
    virtual void lowerAmmo(units_t how_much)=0;
    virtual char printType()=0;




};


}
#endif