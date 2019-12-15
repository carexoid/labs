#ifndef TESTINGBACK_H
#define TESTINGBACK_H

#include<iostream>
#include<vector>
#include<string>
#include"book.h"
#include"author.h"

void testingFunctions(){
    std::vector<Author*>  authors = { new Author("John", "sci-fi", {"Biggie", "Runner", "Johny", "John"}),
                                     new Author("Bob", "drama", {"Bobbie", "Robin"}),
                                     new Author("Ronnie", "comedy", {"Roberto", "Ron"})};
    std::vector<Book*> parts = {new Book1("Down",  10, 10, 2018, "comedy", 400, "Biggie"),
                                new Book3("Up", 10, 10, 2018, "comedy", 470,{{"Ron", 43},{"John", 42},{"Runner",15}})};
    std::vector<Book*> books = {new Book1("Rollercoaster", 27, 11, 2003, "sci-fi",500, "Johny"),
                                new Book2("Rollercoaster 2", 27, 1, 2006, "sci-fi", 700, {"Johny", "Robin"}),
                                new Book3("Trilling book", 6, 9, 2010, "drama", 670,{{"Ron", 43},{"John", 42},{"Runner",15}}),
                                new Book4("Trilling book 2", 6, 9, 2018, "drama", 890,{{"Ron", 58},{"John", 42}}),
                                new Book5("UpAndDown", 10, 10, 2018, "comedy", 870, parts)};
    auto res1 = getAuthorsOfThisBook(books[2], authors);
    for (const auto& i:res1)
        std::cout << i.first << ":" << i.second << '\n';
    auto res2 = getNumOfBooksAndPages(*authors[0],books,{3, 1, 2009},{7, 11, 2019});
        std::cout << res2.first << "::" << res2.second << std::endl;

}
#endif // TESTINGBACK_H
