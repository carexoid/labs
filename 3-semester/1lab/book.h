//
// Created by daniil on 01.10.2019.
//

#ifndef INC_1LAB_BOOK_H
#define INC_1LAB_BOOK_H

#include<vector>
#include<string>
#include<cassert>
#include<fstream>
#include<algorithm>

//#include <bits/unordered_set.h>

using std::vector;
using std::string;
using std::pair;
//using std::unordered_set;

class Character;

//bool operator == (Character &a,Character &b);

class Book{
private:
    string name;
    string author;
    struct Date{
        int day;
        int month;
        int year;
    } date;
    int pages;
    string annotation;
    vector< Character* > mainCh;
    vector < Character* > secondaryCh;
    vector < Character* > episodicCh;

public:
    Book ();
    Book (string initName,string initAuthor,int initDay, int initMonth, int initYear,int initPages);
    Book (string initName,string initAuthor,int initDay, int initMonth, int initYear,int initPages,const vector< Character*> & initMain, const vector< Character*> & initSecondary, const vector< Character*> & initEpisodic );
    ~Book();

    void setName (string inName);
    void setAuthor (string inAuthor);
    void setDate (int inDay, int inMonth, int inYear);
    void setPages (int inPages);
    void setAnno ();

    void addAnnotation (string inputTXTname);
    void addMain(Character* newMain);
    void addSecondary(Character* newSecondary);
    void addEpisodic(Character* newEpi);
    void addCharacter(Character* newCh, int status);

    string getName ();
    string getAuthor ();
    string getDateAsStr ();
    int getDay ();
    int getMonth();
    int getYear();
    int getPages();
    string getAnno ();
    vector<Character*> getMain();
    vector<Character*> getSecondary();
    vector<Character*> getEpisodic();

    int statusOf(Character* ch);
};

bool operator == (Book &a, Book &b);
template<typename T>
std::ostream& operator << (std::ostream& outp, const vector<T>& vec);

std::ostream& operator << (std::ostream& outp, Book& book);

bool cmp(Book &a, Book &b);

bool chFinder (vector<Character> vec, Character &ch);
vector< pair< Character*, vector <Book*> > > seriesDivider (vector<Book> &input);

Book operator + (Book &a, Book &b);

bool operator < (Book a, Book b);

#endif //INC_1LAB_BOOK_H
