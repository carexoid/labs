#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>


class Author
{
public:
    Author();
    Author(const std::string& name, const std::string& genre, const std::vector<std::string>& nicks);

    std::string getName() const;
    std::string getGenre() const;
    std::vector<std::string> getNicks() const;

private:
    std::string _name;
    std::string _genre;
    std::vector<std::string> _nicks;

};

#endif // AUTHOR_H
