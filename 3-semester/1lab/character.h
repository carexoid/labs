//
// Created by daniil on 01.10.2019.
//

#ifndef INC_1LAB_CHARACTER_H
#define INC_1LAB_CHARACTER_H


#include<vector>
#include<string>


using std::vector;
using std::string;
using std::pair;

class Book;

//bool operator == (Book &a,Book &b);

class Character {
private:
    vector<string> nicks;
    vector< pair<Book*,int> > mentions;
public:
    Character() = default;
    Character (const vector<string> &inNicks, const vector< pair<Book*,int> > &inMentions);

    void addNick (const string &newNick);
    void addBook (Book* newBook, int status);

    vector<string> getNicks() const;
    vector< pair<Book*,int> > getMentions();

    bool hasNick (const string &inNick) const ;
    //returns status in needed book or 0 if not mentioned in needed book
    int mentionedInAs (Book* inBook);

    void synchroWithBooks();

};


bool operator == (Character &a,Character &b);


#endif //INC_1LAB_CHARACTER_H
