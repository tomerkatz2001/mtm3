#include <memory>
template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}
enum Team { CPP, PYTHON };
enum CharacterType {SOLDIER, MEDIC, SNIPER};
typedef int units_t;

class Charachter{
    double health;
    int ammo;
    const int range;
    const double damage;
    Team team;
}
class Soldier:public Charachter{
    Soldier(double h,int a,int r,double d,Team t):health(h),ammo(a),range(r),damage(d),Team(t){}

}
class Medic:public Charachter{
    Medic(int a,double h,int r,double d,Team t):health(h),ammo(a),range(r),damage(d),Team(t){}
}
class Sniper:public Charachter{
    Sniper(int a,double h,int r,double d,Team t):health(h),ammo(a),range(r),damage(d),Team(t){}
}
class Game{
    std::shared_ptr<Character>[][] board;
    int height;
    int width;
    Game(int height, int width);

    Game(const Game& other);
    Game& operator=(const Game& other);

    void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

    void reload(const GridPoint & coordinates);

    bool isOver(Team* winningTeam=NULL) const;

}
Game::Game(int height, int width):board(Dimensions(height,width),NULL),height(height),width(width){};
Game::Game(const Game& other){
    this->height=other.height;
    this->width=other.width;
    for(int i=0;i<=this->height;i++){ 
        for(int j=0;j<=this->height;j++){
            if( instanceof<Soldier>(this->board[i][j]*)){
                this->board[i][j]=new Soldier(other.board[i][j]->health,other.board[i][j]->ammo,other.board[i][j]->range,other.board[i][j]->damage,other.board[i][j]->team);
            }
            if( instanceof<Medic>(this->board[i][j]*)){
                this->board[i][j]=new Medic(other.board[i][j]->health,other.board[i][j]->ammo,other.board[i][j]->range,other.board[i][j]->damage,other.board[i][j]->team);
            }
            if( instanceof<Sniper>(this->board[i][j]*)){
                this->board[i][j]=new Sniper(other.board[i][j]->health,other.board[i][j]->ammo,other.board[i][j]->range,other.board[i][j]->damage,other.board[i][j]->team);
            }
        }
    }
}
//        if(!((src_coordinates.y==dst_coordinates.y && (src_coordinates.x<=dst_coordinates+3 && src_coordinates.x>=dst_coordinates.x-3)) || (src_coordinates.x==dst_coordinates.x && (src_coordinates.y<=dst_coordinates.y+3 && src_coordinates.y>=dst_coordinates.y-3)))){

void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates){
    if(dst_coordinates.y>=this->height||dst_coordinates.x>=this->width||src_coordinates.y>=this->height||src_coordinates.x<0||dst_coordinates.y<0||dst_coordinates.x<0||src_coordinates.y<0||src_coordinates.x<0){
        throw IllegalCell();
    }
    if(this->board[src_coordinates.y][src_coordinates.x]==NULL){
        throw CellEmpty();
    }
    if(this->board[dst_coordinates.y][dst_coordinates.x]!=NULL){
        throw CellOccupied();
    }
    if( instanceof<Soldier>){
        if(distance(src_coordinates,dst_coordinates)>3){
            throw MoveToFar();
        }
    }
    if( instanceof<Medic>(this->board[src_coordinates.y][src_coordinates.x]*)){
        if(distance(src_coordinates,dst_coordinates)>5){
            throw MoveToFar();
        }
    }
    if( instanceof<Sniper>(this->board[src_coordinates.y][src_coordinates.x]*)){
        if(distance(src_coordinates,dst_coordinates)>4){
            throw MoveToFar();
        }
    }
    this->board[dst_coordinates.y][dst_coordinates.x]=this->board[src_coordinates.y][src_coordinates.x];
    this->board[src_coordinates.y][src_coordinates.x]=NULL;
}

void Game::reload(const GridPoint & coordinates){
    if(coordinates.y>=this->height||coordinates.x>=this->width||coordinates.y<0||coordinates.x<0){
        throw IllegalCell();
    }
    if(this->board[coordinates.y][coordinates.x]==NULL){
        throw CellEmpty();
    }
    if( instanceof<Soldier>){
        this->board[coordinates.y][coordinates.x]->ammo+=3;
    }
    if( instanceof<Medic>(this->board[src_coordinates.y][src_coordinates.x]*)){
        this->board[coordinates.y][coordinates.x]->ammo+=5;
    }
    if( instanceof<Sniper>(this->board[src_coordinates.y][src_coordinates.x]*)){
        this->board[coordinates.y][coordinates.x]->ammo+=2;
    }
}
bool Game::bool isOver(Team* winningTeam){
    bool team1=false;
    bool team2=false;
    for(int i=0;i<=this->height;i++){ 
        for(int j=0;j<=this->height;j++){
            if(this->board[i][j]!=NULL){
                if(this->board[i][j]->team==Team.CPP){
                    team1=true;
                }
                if(this->board[i][j]->team==Team.Python){
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
                winningTeam=Team.CPP;
            }
            if(team2){
                winningTeam=Team.Python;
            }
        }
        return true;
    }
}