#include "Character.h"

mtm::Character::Character(mtm::Team team, units_t health, units_t ammo, units_t range, units_t power):
health(health),
ammo(ammo),
range(range),
power(power),
team(team){}

mtm::units_t mtm::Character::getAttackCost() const
{
    return attack_cost;
}
mtm::units_t mtm::Character::getMaxMove() const
{
    return max_move;
}
void mtm::Character::rechargeAmmo()
{
    ammo+=recharge_ammo;
}
mtm::units_t mtm::Character::getHealth()const{
    return health;
}
mtm::units_t mtm::Character::getAmmo()const
{
    return ammo;
}
mtm::units_t mtm::Character::getRange()const
{
    return range;
}
mtm::units_t mtm::Character::getPower()const
{
    return power;
}
mtm::Team mtm::Character::getTeam()const
{
    return team;
}
void mtm::Character::lowerHealth(units_t how_much)
{
    health-=how_much;
}


  
    