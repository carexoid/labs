#include "author.h"

Author::Author(){}

Author::Author(const std::string &name, const std::string &genre, const std::vector<std::string>& nicks)
    : _name(name), _genre(genre), _nicks(nicks){}

std::string Author::getName() const{
    return _name;
}

std::string Author::getGenre() const{
    return _genre;
}
std::vector<std::string> Author::getNicks() const{
    return _nicks;
}
