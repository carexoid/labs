#ifndef BOOK_H
#define BOOK_H

#include<string>
#include<vector>
#include"author.h"

class Author;

class Book;

struct AuthorData{
    std::string nick;
    Book* part;
    int pages;
};

struct Date{
    int day;
    int month;
    int year;
};

class Book
{
public:
    Book();
    Book(const std::string& name, int day, int month, int year, const std::string& genre, int size);
    virtual ~Book();
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    Date getDate() const;
    std::string getName() const;
    std::string getGenre() const;
    int getType() const;
    int getSize() const;
    virtual std::vector<AuthorData> getAuthors() = 0;

protected:
    int _type;
    std::string _name;
    int _day;
    int _month;
    int _year;
    std::string _genre;
    int _size;
};

class Book1 : public Book{
public:
    Book1(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::string& author);
    ~Book1() override;
    std::vector<AuthorData> getAuthors() override;

private:
    std::string _author;
};

class Book2 : public Book{
public:
    Book2(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::string>& authors);
    ~Book2() override;
    std::vector<AuthorData> getAuthors() override;

private:
    std::vector<std::string> _authors;
};


class Book3 : public Book{
public:
    Book3(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::pair<std::string, int> >& authors);
    ~Book3() override;
    std::vector<AuthorData> getAuthors() override;

private:
    std::vector<std::pair<std::string, int> > _authors;

};

class Book4 : public Book{
public:
    Book4(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<std::pair<std::string, int> >& authors);
    ~Book4() override;
    std::vector<AuthorData> getAuthors() override;

private:
    std::vector<std::pair<std::string, int> > _authors;

};

class Book5 : public Book{
public:
    Book5(const std::string &name, int day, int month, int year, const std::string &genre, int size, const std::vector<Book*>& parts);
    ~Book5() override;
    std::vector<AuthorData> getAuthors() override;
private:
    std::vector<Book*> _parts;
};

std::vector<std::pair<std::string, int> > getAuthorsOfThisBook(Book* book, const std::vector<Author*>& authors);

std::pair<int, int> getNumOfBooksAndPages (const Author& author, const std::vector<Book*>& books,Date from, Date to);



#endif // BOOK_H
