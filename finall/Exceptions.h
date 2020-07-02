#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
namespace mtm{
class Exception: public std::exception{};
class GameException: public Exception{};
class IllegalArgument:public GameException{
    public:
    const char* what() const noexcept;
};
class IllegalCell: public GameException{
    public:
    const char* what() const noexcept;
};
class CellEmpty: public GameException{
    public:
    const char* what() const noexcept;
};
class MoveTooFar:public GameException{
    public:
    const char* what() const noexcept;
};
class CellOccupied:public GameException{
    public:
    const char* what() const noexcept;
};
class OutOfRange:public GameException{
    public:
    const char* what() const noexcept;
};
class OutOfAmmo:public GameException{
    public:
    const char* what() const noexcept;
};
class IllegalTarget:public GameException{
    public:
    const char* what() const noexcept;
}; 
}
#endif