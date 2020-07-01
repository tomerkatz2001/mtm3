#ifndef GAME_H
#define GAME_H
#include"Auxiliaries.h"
#include"Character.h"
#include<memory>
#include<vector>

namespace mtm{
class Game{

    public:
    std::vector<std::vector<std::shared_ptr<Character>>> board;
    Game(int height, int width);
    ~Game()=default;
    Game(const Game& other);
    Game& operator=(const Game& other);
    //friend std::ostream& operator<<(std::ostream& os, const Game& game);
    void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
    static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
    units_t health, units_t ammo, units_t range, units_t power);

    void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
    void reload(const GridPoint & coordinates);


    bool isOver(Team* winningTeam=NULL) const;

};
std::ostream& operator<<(std::ostream& os, const Game& game);
}

#endif