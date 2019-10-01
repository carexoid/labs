//
// Created by daniil on 01.10.2019.
//


#include "book.h"
#include "character.h"
#include "graph.h"


Book::Book (){
    date ={0,0,0};
    pages = 0;
};
Book::Book (string initName,string initAuthor,int initDay, int initMonth, int initYear,int initPages) : name(initName), author(initAuthor), date ({initDay,initMonth,initYear}), pages(initPages){
    annotation = name + "_" + author + std::to_string(date.day) + "_" + std::to_string(date.month) + "_" + std::to_string(date.year) + ".txt";
}
Book::Book (string initName,string initAuthor,int initDay, int initMonth, int initYear,int initPages,const vector< Character*> & initMain, const vector< Character*> & initSecondary, const vector< Character*> & initEpisodic )
        : Book(initName,initAuthor,initDay,initMonth,initYear,initPages){
    mainCh = initMain;
    secondaryCh = initSecondary;
    episodicCh = initEpisodic;
}
Book::~Book(){};

void Book::setName (string inName){
    if (name != "")
        name = inName;
}
void Book::setAuthor (string inAuthor){
    if (author!= "")
        author = inAuthor;
}
void Book::setDate (int inDay, int inMonth, int inYear){
    if (!date.day)
        date = {inDay,inMonth,inYear};
}
void Book::setPages (int inPages){
    if (!pages)
        pages = inPages;
}
void Book::setAnno (){
    if (annotation!= "")
        annotation = name + "_" + author + std::to_string(date.day) + "_" + std::to_string(date.month) + "_" +std:: to_string(date.year) + ".txt";
}

void Book::addAnnotation (string inputTXTname){
    std::ifstream input(inputTXTname);
    setAnno();
    char c;
    std::ofstream output(annotation);
    while (input >> c){
        output << c;
    }
    input.close();
    output.close();
}
void Book::addMain(Character* newMain){
    mainCh.push_back(newMain);
}
void Book::addSecondary(Character* newSecondary){
    secondaryCh.push_back(newSecondary);
}
void Book::addEpisodic(Character* newEpi){
    episodicCh.push_back(newEpi);
}
void Book::addCharacter(Character* newCh, int status){
    assert(status > 0 && status < 4);
    if (status == 1)
        addMain(newCh);
    else if (status == 2)
        addSecondary(newCh);
    else if (status == 3)
        addEpisodic(newCh);
}

string Book::getName (){
    return name;
}
string Book::getAuthor (){
    return  author;
}
string Book::getDateAsStr (){
    return std::to_string(date.day) + "." + std::to_string(date.month) + "." + std::to_string(date.year);
}
int Book::getDay (){
    return  date.day;
}
int Book::getMonth(){
    return date.month;
}
int Book::getYear(){
    return date.year;
}
int Book::getPages(){
    return pages;
}
string Book::getAnno (){
    return annotation;
}
vector<Character*> Book::getMain(){
    return mainCh;
}
vector<Character*> Book::getSecondary(){
    return secondaryCh;
}
vector<Character*> Book::getEpisodic(){
    return episodicCh;
}

int Book::statusOf(Character* ch){
    for (auto &c: mainCh)
        if (*c == *ch)
            return 1;
    for (auto &c: secondaryCh)
        if(*c == *ch)
            return 2;
    for (auto &c: episodicCh)
        if (*c == *ch)
            return 3;
    return 0;
}

bool operator == (Book &a, Book &b){
    return (a.getName() == b.getName() && a.getAuthor() == b.getAuthor() && a.getDateAsStr() == b.getDateAsStr());
}
bool cmpForBooks(Book* a, Book* b){
    if (a->getYear() == b->getYear()){
        if (a->getMonth() == b->getMonth())
            return a->getDay() < b->getDay();
        return a->getMonth() < b->getMonth();
    }
    return a->getYear() < b->getYear();
}

bool chFinder (vector<Character> vec, Character &ch){
    for (auto &c: vec){
        if (ch == c)
            return 1;
    }
    return 0;
}
vector< pair< Character*, vector <Book*> > > seriesDivider (vector<Book> &input){
    vector< pair< Character*, vector <Book*> > > series;
    vector <Character> allCharacters;
    for (auto &b: input){
        for (auto &bm: b.getMain()){
            if (!chFinder(allCharacters,*bm))
                allCharacters.push_back(*bm);
        }
        for (auto &bs: b.getSecondary()){
            if (!chFinder(allCharacters,*bs))
                allCharacters.push_back(*bs);
        }
    }
    for (auto &ac: allCharacters){
        vector<Book*> booksInSeries;
        for (auto &bc: ac.getMentions() ){
            if (bc.second == 1 || bc.second == 2)
                booksInSeries.push_back(bc.first);
        }
        std::sort(booksInSeries.begin(), booksInSeries.end(), &cmpForBooks);
        series.emplace_back(&ac,booksInSeries);

    }
    return series;

}

std::ostream& operator << (std::ostream& outp, Book& book){
    outp << "Name: " << book.getName() << "; Author: " << book.getAuthor() << "; Date: " << book.getDateAsStr();
    if (!book.getMain().empty()){
        outp << "; Main Characters: ";
        for (auto &b: book.getMain()){
            if (!b->getNicks().empty())
                outp << b->getNicks();
        }
    }
    if (!book.getSecondary().empty()){
        outp << "; Secondary Characters: ";
        for (auto &b: book.getSecondary()){
            if (!b->getNicks().empty())
                outp << b->getNicks();
        }
    }
    if (!book.getEpisodic().empty()){
        outp << "; Episodic Characters: ";
        for (auto &b: book.getEpisodic()){
            if (!b->getNicks().empty())
                outp << b->getNicks();
        }
    }
    return outp;
}

template<>
Book getData<Book> (int index){
    return Book(std::to_string(0),std::to_string(0),0,0,0,index);
}

Book operator + (Book &a, Book &b){
    return Book(std::to_string(0),std::to_string(0),0,0,0,a.getPages() + b.getPages());
}

bool operator < (Book a, Book b){
    return a.getPages() < b.getPages();
}

