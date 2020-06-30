#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
namespace mtm{
class Exception: public std::exception{};
class GameException: public Exception{};
class IllegalArgument:public GameException{
    const char* what() const throw();
};
class IllegalCell: public GameException{
    const char* what() const throw();
};
class CellEmpty: public GameException{
    const char* what() const throw();
};
class MoveTooFar:public GameException{
    const char* what() const throw();
};
class CellOccupied:public GameException{
    const char* what() const throw();
};
class OutOfRange:public GameException{
    const char* what() const throw();
};
class OutOfAmmo:public GameException{
    const char* what() const throw();
};
class IllegalTarget:public GameException{
    chonst char* what() const throw();
}; 
#endif