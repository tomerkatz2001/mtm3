#include "Medic.h"

mtm::Medic::Medic(mtm::Team team, units_t health, units_t ammo, units_t range, units_t power):
Character(team,health,ammo,range,power)
{
    attack_cost=MEDIC_ATTACK_COST;
    max_move=MEDIC_MAX_MOVE;
    recharge_ammo=MEDIC_RELOAD;
    
}
char mtm::Medic::printType()
{
    if (team==CPP)
    {
        return 'M';
    }
    else
    {
        return 'm';
    }
    
}
void mtm::Medic::lowerAmmo(units_t how_much)
{
    ammo-=how_much;
}