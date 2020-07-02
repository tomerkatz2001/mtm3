#include "Sniper.h"

mtm::Sniper::Sniper(mtm::Team team, units_t health, units_t ammo, units_t range, units_t power):
Character(team,health,ammo,range,power)
{
    attack_cost=SNIPER_ATTACK_COST;
    max_move=SNIPER_MAX_MOVE;
    recharge_ammo=SNIPER_RELOAD;
    
}

char mtm::Sniper::printType()
{
    if(team==CPP)
    {
        return 'N';
    }
    else
    {
        return 'n';
    }
    
}
void mtm::Sniper::lowerAmmo(units_t how_much)
{
    ammo-=how_much;
}
