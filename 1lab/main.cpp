#include <iostream>
#include "graph.h"
#include "book.h"
#include "character.h"


using std::cout;
using std::cin;
using std::vector;
using std::pair;

void testInt(){
    cout << "\n\nDemonstrating INT\n\n";
    int minDist = 0, maxDist = 10000;
    vector<int> initNodes = {12, 34, 56, 78, 90};
    vector< pair< pair<int,int>, int> > initEdges = { { {1,2}, 100}, {{2, 3} , 200} , {{4,5}, 300} , {{2,5}, 400} };
    MatrixBasedGraph<int,int> mgraph(initNodes,initEdges);
    vector <pair<int,int> > vec = { {1,310}, {2,810}};
    mgraph.addNode(21,vec);
    mgraph.addEdge( 520,mgraph.findNode(56), mgraph.findNode(90));
    mgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << mgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << mgraph.isConnected() << '\n';
    mgraph.delNode(2);
    mgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << mgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << mgraph.isConnected() << '\n';

    //doing absolutely the same with list based graph

    ListBasedGraph<int,int> lgraph(initNodes,initEdges);
    lgraph.addNode(21,vec);
    lgraph.addEdge( 520,lgraph.findNode(56), lgraph.findNode(90));
    lgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << lgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << lgraph.isConnected() << '\n';
    lgraph.delNode(2);
    lgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << lgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << lgraph.isConnected() << '\n';

}

void testDouble(){
    cout << "\n\nDemonstrating DOUBLE\n\n";
    double minDist = 0, maxDist = 10000;
    vector<double> initNodes = {12.1, 34.1, 56.1, 78.1, 90.1};
    vector< pair< pair<int,int>, double> > initEdges = { { {1,2}, 100.1}, {{2, 3} , 200.1} , {{4,5}, 300.1} , {{2,5}, 400.1} };
    MatrixBasedGraph<double,double> mgraph(initNodes,initEdges);
    vector <pair<int,double> > vec = { {1,310.1}, {2,810.1}};
    mgraph.addNode(21.1,vec);
    mgraph.addEdge( 520,mgraph.findNode(56.1), mgraph.findNode(90.1));
    mgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << mgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << mgraph.isConnected() << '\n';
    mgraph.delNode(2);
    mgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << mgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << mgraph.isConnected() << '\n';

    //doing absolutely the same with list based graph

    ListBasedGraph<double,double> lgraph(initNodes,initEdges);
    lgraph.addNode(21.1,vec);
    lgraph.addEdge( 520,lgraph.findNode(56.1), lgraph.findNode(90.1));
    lgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << lgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << lgraph.isConnected() << '\n';
    lgraph.delNode(2);
    lgraph.printGraph();
    cout << "Distance from 1 to 5 is "  << lgraph.countDist(1,5,minDist,maxDist) << '\n';
    cout << "Is connected: " << lgraph.isConnected() << '\n';

}

void bookTester (){
    cout << "\n\nDemonstrating Books abilities and books as nodes\n\n";
    vector<Book> books = { {"Harry Potter 2", "Roaling", 24, 10, 1997,600},
                           {"Harry Potter", "Roaling", 23, 7, 1995,500},
                           {"Persie Jackson", "Riordan", 3, 5,2003, 700},
                           {"Dambldor Story", "Smbd", 5,12,2018,200}} ;
    Character harry, persie, dambl;
    dambl.addNick("Dambldor");
    harry.addNick("Harry Potter");
    persie.addNick("Persie Jackson");
    dambl.addBook(&books[0],2);
    dambl.addBook(&books[1],2);
    dambl.addBook(&books[3],1);
    harry.addBook(&books[0],1);
    harry.addBook(&books[1],1);
    harry.addBook(&books[3],3);
    persie.addBook(&books[2],1);
    cout << harry.mentionedInAs(&books[1]);
    books[0].addMain(&harry);
    books[1].addCharacter(&harry,1);
    books[2].addCharacter(&harry,1);
    books[3].addEpisodic(&harry);
    dambl.synchroWithBooks();
    vector<Character*> rolesGot = books[3].getMain();
    if (rolesGot[0]->getNicks() == dambl.getNicks())
        cout<<"\nDambldor is main character of book Dambldor story";
    vector< pair<Character*, vector <Book*> > > divided = seriesDivider(books);
    vector<string> nicksOfSmbd = divided[1].first->getNicks();
    cout << "\nSeries of books with " <<  nicksOfSmbd[0] << ": ";
    for (auto &c: divided[1].second){
        cout << c->getName() << ", ";
    }
    vector< pair< pair<int,int>, double> > initEdges = { { {1,2}, 100.1}, {{2, 3} , 200.1} , {{2,4}, 300.1} , {{1,4}, 400.1} };
    MatrixBasedGraph<Book,double> mgraph(books,initEdges);
    mgraph.printGraph();

}

void testVectorAndBooks(){
    cout << "\n\nDemonstrating vector<string> as nodes and books as edges\n\n";
    vector<Book> books = { {"Harry Potter 2", "Roaling", 24, 10, 1997,600},
                           {"Harry Potter", "Roaling", 23, 7, 1995,500},
                           {"Persie Jackson", "Riordan", 3, 5,2003, 700},
                           {"Dambldor Story", "Smbd", 5,12,2018,200}} ;
    Character harry, persie, dambl;
    dambl.addNick("Dambldor");
    harry.addNick("Harry Potter");
    persie.addNick("Persie Jackson");
    dambl.addBook(&books[0],2);
    dambl.addBook(&books[1],2);
    dambl.addBook(&books[3],1);
    harry.addBook(&books[0],1);
    harry.addBook(&books[1],1);
    harry.addBook(&books[3],3);
    persie.addBook(&books[2],1);
    books[0].addMain(&harry);
    books[1].addCharacter(&harry,1);
    books[2].addCharacter(&harry,1);
    books[3].addEpisodic(&harry);
    dambl.synchroWithBooks();
    vector<vector<string> > input = {{"qwe","rty","uio"},
                                     {"asd","fgh"},
                                     {"zxc","vbn","hjk"},
                                     {"huo","i"}};
    vector< pair< pair<int,int>, Book > > initEdges = { { {1,2}, books[0]}, {{2, 3} , books[1]} , {{2,4}, books[3]} , {{1,4}, books[2]} };

    MatrixBasedGraph<vector<string>,Book> mgraph(input, initEdges);
    mgraph.printGraph();
    books.push_back(mgraph.countDist(1,3,0,100000));
    cout<<"To get from 1 node to 3 you need to pass " << books[4].getPages() << " pages";
}
int main() {

    testInt();
    testDouble();
    bookTester();
    testVectorAndBooks();
    return 0;
}