
#include<math.h>
#include "Sniper.h"
#include"Soldier.h"
#include"Medic.h"
#include "Game.h"
#include <assert.h>
#include "Exceptions.h"

static mtm::CharacterType getType(const mtm::Game& game, int i,int j)
{
    mtm::CharacterType type;
    if(game.board[i][j]->printType()=='S'||game.board[i][j]->printType()=='s')
    {
        type=mtm::SOLDIER;
    }
    if(game.board[i][j]->printType()=='M'||game.board[i][j]->printType()=='m')
    {
        type=mtm::MEDIC;
    }
    if(game.board[i][j]->printType()=='N'||game.board[i][j]->printType()=='n')
    {
        type=mtm::SNIPER;
    }
    return type;   
}
static std::shared_ptr<mtm::Character> cloneCharacter(const mtm::Game& game, int i,int j)
{
    assert(game.board.at(i).at(j)!=nullptr);
    mtm::units_t copy_health=game.board.at(i).at(j)->getHealth();
    mtm::units_t copy_ammo=game.board.at(i).at(j)->getAmmo();
    mtm::units_t copy_range=game.board.at(i).at(j)->getRange();
    mtm::units_t copy_power=game.board.at(i).at(j)->getPower();
    mtm::CharacterType copy_type=getType(game,i,j);
    mtm::Team copy_team=game.board.at(i).at(j)->getTeam();
    return mtm::Game::makeCharacter(copy_type,copy_team,copy_health,copy_ammo,copy_range,copy_power);
}



mtm::Game::Game(int height, int width)
{ 
    if(height<=0 || width<=0)
    {
        throw mtm::IllegalArgument();
    }
    board.resize(height);
    for(int i=0;i<height;i++)
    {
        std::vector<std::shared_ptr<mtm::Character>> row_i(width);
        for (std::vector<std::shared_ptr<mtm::Character>>::iterator it = row_i.begin(); it != row_i.end(); ++it)
        {
           *it=nullptr; 
        }

       board[i]=row_i; 
    }
}

mtm::Game::Game(const mtm::Game& other)
{ 
    int board_width= other.board.at(0).size();
    int board_height=other.board.size();
    board.resize(board_height);
    for(int i=0;i<board_height;i++)
    {
        std::vector<std::shared_ptr<mtm::Character>> row_i(board_width);
        for(int j=0;j<board_width;j++)
        {
            if(other.board.at(i).at(j)!=nullptr)
            { 
                board[i][j]=cloneCharacter(other,i,j);
            }
        }
    }
}


void mtm::Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{

    int board_width=board.at(0).size();
    int board_height=board.size();
    if(dst_coordinates.row>=board_height||dst_coordinates.col>=board_width\
    ||src_coordinates.row>=board_height||src_coordinates.col>=board_height\
    ||src_coordinates.row<0||dst_coordinates.col<0||dst_coordinates.row<0||\
    src_coordinates.col<0||src_coordinates.row<0)
    {
        throw mtm::IllegalCell();
    }
    if(board.at(src_coordinates.row).at(src_coordinates.col)==nullptr){
        throw mtm::CellEmpty();
    }
         if(dst_coordinates.row==src_coordinates.row&&dst_coordinates.col==src_coordinates.col)
     {
         return; //no need to move
     }
    if(board.at(dst_coordinates.row).at(dst_coordinates.col)!=nullptr){
       throw mtm::CellOccupied();
    }
    if(board.at(src_coordinates.row).at(src_coordinates.col)->getMaxMove()<\
    mtm::GridPoint::distance(src_coordinates,dst_coordinates))
    {
      throw mtm::MoveTooFar();  
    }
    board[dst_coordinates.row][dst_coordinates.col]=board.at(src_coordinates.row).at(src_coordinates.col);
    board[src_coordinates.row][src_coordinates.col]=nullptr;
}


std::ostream& mtm::operator<<(std::ostream& os, const mtm::Game& game)
{
    int board_width= game.board.at(0).size();
    int board_height=game.board.size();
    int matrix_cells=board_width*board_height;
    std::vector<std::vector<char>> copy(board_height);
    for (std::vector<std::vector<char>>::iterator it1 = copy.begin(); it1 != copy.end(); ++it1)
    {
        std::vector<char> row_i(board_width);
        for (std::vector<char>::iterator it2 = row_i.begin(); it2 != row_i.end(); ++it2)
        {
           *it2=' '; 
        }
        (*it1)=row_i;
    }

     for(int i=0;i<board_height;i++)
     {
         for(int j=0;j<board_width;j++)
         {
             if(game.board.at(i).at(j)!=nullptr)
             {
                 copy[i][j]=game.board.at(i).at(j)->printType();
             }
         }
     }
    std::string map_str;
    for (std::vector<std::vector<char>>::iterator it1 = copy.begin(); it1 != copy.end(); ++it1)
    {
        for(std::vector<char>::iterator it2=(*it1).begin();it2!=(*it1).end();it2++)
        {
            map_str.append(std::string(1,*it2));//this makes the char to string and after that append it.
        }
    }

    
    return mtm::printGameBoard(os,map_str.c_str(),(map_str.c_str())+matrix_cells,board_width);
}


void mtm::Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character)
{   
    int board_width= board.at(0).size();
    int board_height=board.size();

    if(coordinates.col<0||coordinates.row<0||\
    coordinates.col>=board_width||coordinates.row>=board_height)//if its out of the board
    {
        throw mtm::IllegalCell();
    }
    if(board.at(coordinates.row).at(coordinates.col)!=nullptr)//if cell is taken
    {
        throw mtm::CellOccupied();
    }

    board.at(coordinates.row).at(coordinates.col)=character;

}
std::shared_ptr<mtm::Character> mtm::Game::makeCharacter(mtm::CharacterType type,mtm::Team team,
units_t health, units_t ammo, units_t range, units_t power)
{
    if(health<=0||ammo<0||range<0||power<0)
    {
        throw IllegalArgument();
    }
    if(type==mtm::SOLDIER)
    {
        return std::shared_ptr<Character>(new mtm::Soldire(team,health,ammo,range,power));
    }
    if(type==mtm::MEDIC)
    {
        return std::shared_ptr<Character>(new mtm::Medic(team,health,ammo,range,power));
    }
    //else the type is Medic
    
        return std::shared_ptr<Character>(new mtm::Medic(team,health,ammo,range,power));
    

}


mtm::Game& mtm::Game::operator=(const mtm::Game& other)
{   
    int other_board_width=other.board.at(0).size();
    int other_board_height=other.board.size();

    std::vector<std::vector<std::shared_ptr<Character>>> empty_mat(other_board_height);
    for(int i=0;i<other_board_height;i++)
    {
        std::vector<std::shared_ptr<mtm::Character>> row_i(other_board_width);
        for (std::vector<std::shared_ptr<mtm::Character>>::iterator it = row_i.begin(); it != row_i.end(); ++it)
        {
           *it=nullptr; 
        }
       empty_mat[i]=row_i; 
    }
    

    for(int i=0;i<other_board_height;i++)
    {
        for(int j=0;j<other_board_width;j++)
        {
            if(other.board.at(i).at(j)!=nullptr)
            { 
                empty_mat[i][j]=cloneCharacter(other,i,j);

            }
        }
    }
    board=empty_mat;
    return *this;


}

static void soldierAttack(mtm::Game& game,const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates)
{
    
    int attacker_row=src_coordinates.row;
    int attacker_col=src_coordinates.col;
    assert(game.board.at(attacker_row).at(attacker_col)!=NULL);
    mtm::Team attacker_team=game.board.at(attacker_row).at(attacker_col)->getTeam();
    int board_width= game.board.at(0).size();
    int board_height=game.board.size();
    int soldier_range=game.board.at(attacker_row).at(attacker_col)->getRange();
    int soldier_power=game.board.at(attacker_row).at(attacker_col)->getPower();
    if(game.board.at(attacker_row).at(attacker_col)->getAmmo()<\
    game.board.at(attacker_row).at(attacker_col)->getAttackCost())
    {
        throw mtm::OutOfAmmo();
    }
    game.board[attacker_row][attacker_col]->lowerAmmo(1);
    for(int i=0;i<board_height;i++)
    {
        for(int j=0;j<board_width;j++)
        {
            if(game.board.at(i).at(j)!=nullptr){
                mtm::GridPoint current_cell(i,j);
                if((double)mtm::GridPoint::distance(current_cell,dst_coordinates)<=(double)ceil(soldier_range/3.0))
                {
                    
                    if(i!=attacker_row||j!=attacker_col){//not attacting itself
                        if(game.board.at(i).at(j)->getTeam()!=attacker_team)//not the same team
                        {
                            if(mtm::GridPoint::distance(current_cell,dst_coordinates)==0)
                            {
                                game.board[i][j]->lowerHealth(soldier_power);
                                
                            }
                            else{
                                game.board[i][j]->lowerHealth((int)(double)ceil(soldier_power/2.0));  
                            }
                        }
                    }
                }
            }
        }
    }
}
static void medicAttack(mtm::Game& game,const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates)
{
    int attacker_row=src_coordinates.row;
    int attacker_col=src_coordinates.col;
    int attacked_row=dst_coordinates.row;
    int attacked_col=dst_coordinates.col;
    assert(game.board.at(attacker_row).at(attacker_col)!=nullptr);
    int medic_power=game.board.at(attacker_row).at(attacker_col)->getPower();
    if(game.board.at(attacked_row).at(attacked_col)==nullptr)//the cell is empty
    {
        throw mtm::IllegalTarget();
    }
    if(attacked_col==attacker_col&&attacker_row==attacked_row)//not the medic 
    {
        throw mtm::IllegalTarget();
    }
    
    if(game.board.at(attacked_row).at(attacked_col)->getTeam()!= \
    game.board.at(attacker_row).at(attacker_col)->getTeam()) //they are not the same team
    {
        if(game.board.at(attacker_row).at(attacker_col)->getAmmo()<\
        game.board.at(attacker_row).at(attacker_col)->getAttackCost())
        {
            throw mtm::OutOfAmmo();
        }
        
        game.board[attacked_row][attacked_col]->lowerHealth(medic_power);
        game.board[attacker_row][attacker_col]->lowerAmmo(1);
    }
    else//they are the same team
    {
        
        game.board[attacked_row][attacked_col]->lowerHealth(-medic_power);
        
        
    }
}
static void sniperAttack(mtm::Game& game,const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates)
{
    int attacker_row=src_coordinates.row;
    int attacker_col=src_coordinates.col;
    int attacked_row=dst_coordinates.row;
    int attacked_col=dst_coordinates.col;
    assert(game.board.at(attacker_row).at(attacker_col)!=nullptr);
    mtm::Team attacker_team=game.board.at(attacker_row).at(attacker_col)->getTeam();
    int sniper_power=game.board.at(attacker_row).at(attacker_col)->getPower();
    int sniper_range=game.board.at(attacker_row).at(attacker_col)->getRange();
    if(game.board.at(attacked_row).at(attacker_col)==nullptr)//the cell is empty
    {
        throw mtm::IllegalTarget();
    }
    if(game.board.at(attacker_row).at(attacker_col)->getAmmo()<\
    game.board.at(attacker_row).at(attacker_col)->getAttackCost())
    {
        throw mtm::OutOfAmmo();
    }
    if((double)mtm::GridPoint::distance(src_coordinates,dst_coordinates)>=(double)ceil(sniper_range/2.0))
    {
        if(game.board.at(attacked_row).at(attacked_col)->getTeam()!=attacker_team)//not the same team
        {
            if(game.board[attacker_row][attacker_col]->sequence==3)
            {
                game.board[attacked_row][attacked_col]->lowerHealth(sniper_power*2);
                game.board[attacker_row][attacker_col]->sequence-=3;
            }
            else
            {
                game.board[attacked_row][attacked_col]->lowerHealth(sniper_power);
                game.board[attacker_row][attacker_col]->sequence++;   
            }
                    
            game.board[attacker_row][attacker_col]->lowerAmmo(1);
        }
        else{
            throw mtm::IllegalTarget();
        }
    }
}
static void checkForDeads(mtm::Game& game)
{
    int board_width=game.board.at(0).size();
    int board_height=game.board.size();

    for(int i=0;i<board_height;i++)
    {
        for(int j=0;j<board_width;j++)
        {
            if(game.board.at(i).at(j)!=nullptr)
            {
                if(game.board.at(i).at(j)->getHealth()<=0)
                {
                    game.board[i][j]=nullptr;
                }
            }
        }
    }



}


void mtm::Game::attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates)
  {   
    int board_width= board.at(0).size();
    int board_height=board.size();
      if(src_coordinates.row<0||src_coordinates.col<0||dst_coordinates.col<0||dst_coordinates.row<0||\
      src_coordinates.row>=board_height||dst_coordinates.row>=board_height||\
      src_coordinates.col>=board_width||dst_coordinates.col>=board_height)
      {
         throw mtm::IllegalCell();
      }
      if(board.at(src_coordinates.row).at(src_coordinates.col)==nullptr)
      {
          throw mtm::CellEmpty();
      }
      if(board.at(src_coordinates.row).at(src_coordinates.col)->getRange()<\
      mtm::GridPoint::distance(src_coordinates,dst_coordinates))// the range of the character is lower
      {
          throw mtm::OutOfRange();
      }
      if(board.at(src_coordinates.row).at(src_coordinates.col)->getAmmo()<=0)
      {
          throw mtm::OutOfAmmo();
      }

      mtm::CharacterType type=getType(*this,src_coordinates.row,src_coordinates.col);
      if(type==SOLDIER)
      {
          soldierAttack(*this,src_coordinates,dst_coordinates);
      }
      if(type==MEDIC)
      {
          medicAttack(*this,src_coordinates,dst_coordinates);
      }
      if(type==SNIPER)
      {
          sniperAttack(*this, src_coordinates,dst_coordinates);
      }
      checkForDeads(*this);

  }

void mtm::Game::reload(const GridPoint & coordinates){
    if(coordinates.row>=(int)board.size()||coordinates.col>=(int)board.at(0).size()||coordinates.row<0||coordinates.col<0){
        throw mtm::IllegalCell();
    }
    if(board[coordinates.row][coordinates.col]==nullptr){
        throw mtm::CellEmpty();
    }
    board[coordinates.row][coordinates.col]->rechargeAmmo();
}

bool mtm::Game::isOver(Team* winningTeam)const{
    bool team1=false;
    bool team2=false;
    int board_width=board.at(0).size();
    int board_height=board.size();
    for(int i=0;i<=board_height;i++){ 
        for(int j=0;j<=board_width;j++){
            if(board.at(i).at(j)!=nullptr){
                if(board.at(i).at(j)->getTeam()==mtm::CPP){
                    team1=true;
                }
                if(board.at(i).at(j)->getTeam()==mtm::PYTHON){
                    team2=true;
                }
            }
        }
    }
    if(team1&&team2){
        return false;
    }
    else{
        if(winningTeam!=NULL){
            if(team1){
                *winningTeam=mtm::CPP;
            }
            if(team2){
                *winningTeam=mtm::PYTHON;
            }
        }
        return true;
    }
}
