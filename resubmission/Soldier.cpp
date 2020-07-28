#include "Soldier.h"
#include "Character.h"

mtm::Soldire::Soldire(mtm::Team team, units_t health, units_t ammo, units_t range, units_t power):
Character(team,health,ammo,range,power)
{
    attack_cost=SOLDIRE_ATTACK_COST;
    max_move=SOLDIRE_MAX_MOVE;
    recharge_ammo=SOLDIRE_RELOAD;
    
}
char mtm::Soldire::printType()
{
    if(team==CPP)
    {
        return 'S';
    }
    else
    {
        return 's';
    }
    
}
void mtm::Soldire::lowerAmmo(units_t how_much)
{
    ammo-=how_much;
}


