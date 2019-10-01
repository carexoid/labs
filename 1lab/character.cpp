//
// Created by daniil on 01.10.2019.
//



#include "character.h"
#include "book.h"


Character::Character (const vector<string> &inNicks, const vector< pair<Book*,int> > &inMentions) : nicks (inNicks), mentions(inMentions) {}

void Character::addNick (const string &newNick){
    nicks.push_back(newNick);
}
void Character::addBook (Book* newBook, int status){
    mentions.emplace_back(newBook,status);
}

vector<string> Character::getNicks() const{
    return nicks;
}
vector< pair<Book*,int> > Character::getMentions(){
    return mentions;
}

bool Character::hasNick (const string &inNick) const{
    for (auto &n: nicks)
        if (inNick == n)
            return 1;
    return 0;
}
//returns status in needed book or 0 if not mentioned in needed book
int Character::mentionedInAs (Book* inBook){
    for (auto &b: mentions)
        if (*(b.first) == *(inBook))
            return b.second;
    return 0;
}

void Character::synchroWithBooks(){
    for (auto &ment: mentions){
        if (!ment.first->statusOf(this))
            ment.first->addCharacter(this,ment.second);
    }
}

bool operator == (Character &a,Character &b){
    return a.getNicks() == b.getNicks();
}



