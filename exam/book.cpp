#include "book.h"

Book::Book(){}

Book::Book(const std::string &name, int day, int month, int year, const std::string &genre, int sizeOfBook)
    : _name(name), _day(day), _month(month), _year(year), _genre(genre), _size(sizeOfBook){}

std::string Book::getName() const{
    return _name;
}

std::string Book::getGenre() const{
    return _genre;
}

int Book::getDay() const{
    return _day;
}

int Book::getMonth() const{
    return _month;
}

int Book::getYear() const{
    return _year;
}

int Book::getSize() const{
    return _size;
}

int Book::getType() const{
    return _type;
}
Date Book::getDate() const{
    return {_day, _month, _year};
}

Book::~Book(){}

Book1::Book1(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::string& author) :
    Book(name, day, month, year, genre, size), _author(author){
    _type = 1;
}

std::vector<AuthorData> Book1::getAuthors(){
    return {{_author, this, _size}};
}

Book1::~Book1(){}

Book2::Book2(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::string> &authors)
    : Book(name, day, month, year, genre, size), _authors(authors){
    _type = 2;
}

std::vector<AuthorData> Book2::getAuthors(){
    std::vector<AuthorData> res;
    for (int i = 0; i < (int)_authors.size(); i++)
        res.push_back({_authors[i], this, _size / _authors[i].size()});
    return res;
}

Book2::~Book2(){}

Book3::Book3(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::pair<std::string, int> > &authors)
    : Book(name, day, month, year, genre, size), _authors(authors){
    _type = 3;
}

std::vector<AuthorData> Book3::getAuthors(){
    std::vector<AuthorData> res;
    for (int i = 0; i < (int)_authors.size(); i++)
        res.push_back({_authors[i].first, this, _size * _authors[i].second / 100});
    return res;
}

Book3::~Book3(){}

Book4::Book4(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::pair<std::string, int> > &authors)
    : Book(name, day, month, year, genre, size), _authors(authors){
    _authors[0].second += 100;
    _type = 4;
}

std::vector<AuthorData> Book4::getAuthors(){
    std::vector<AuthorData> res;
    for (int i = 0; i < (int)_authors.size(); i++)
        res.push_back({_authors[i].first, this, _size * _authors[i].second / 200});
    return res;
}

Book4::~Book4(){}

Book5::Book5(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<Book *> &parts)
    : Book(name, day, month, year, genre, size), _parts(parts){
    _type = 5;
}

std::vector<AuthorData> Book5::getAuthors(){
    std::vector<AuthorData> res;
    for (const auto& i: _parts){
        std::vector<AuthorData> currentPartRes = i->getAuthors();
        res.insert(res.end(), currentPartRes.begin(), currentPartRes.end());
    }
    return res;
}

Book5::~Book5(){}

std::vector<std::pair<std::string, int> > getAuthorsOfThisBook(Book *book, const std::vector<Author*>& authors){
    std::vector<AuthorData> nicksFromBook = book->getAuthors();
    std::vector<std::pair<std::string, int> > res;
    for (const auto& auth: authors){
        std::string curName = auth->getName();
        std::vector<std::string> curNicks = auth->getNicks();
        int pages = 0;
        for (const auto& nickToFind: curNicks){
            for (const auto& fromBook: nicksFromBook){
                if (fromBook.nick == nickToFind)
                    pages += fromBook.pages;
            }
        }
        if (pages)
            res.push_back({curName,pages});
    }
    return res;
}

namespace dateHelper {
bool lessOrEq (Date left, Date right){
    if(left.year < right.year)
        return true;
    if (left.year == right.year){
        if (left.month < right.month)
            return true;
        if (left.month ==  right.month)
            if (left.day <= right.day)
                return true;
    }
    return false;
}
}

std::pair<int, int> getNumOfBooksAndPages (const Author& author, const std::vector<Book*>& books,Date from, Date to){
    std::vector<std::string> nicks = author.getNicks();
    int numOfBooks = 0, numOfPages = 0;
    for (const auto& curBook: books){
        if (dateHelper::lessOrEq(from, curBook->getDate()) && dateHelper::lessOrEq(curBook->getDate(), to)){
            bool flag = 0;
            std::vector<AuthorData> inBook = curBook->getAuthors();
            for (const auto& curNick: nicks){
                for (const auto& curMention: inBook){
                    if (curNick == curMention.nick){
                        flag = true;
                        numOfPages += curMention.pages;
                    }
                }
            }
            if (flag)
                numOfBooks++;

        }
    }
    return {numOfBooks, numOfPages};
}
