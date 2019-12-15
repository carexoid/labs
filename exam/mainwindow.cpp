#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    authors = {new Author("John", "sci-fi", {"Biggie", "Runner", "Johny", "John"}),
               new Author("Bob", "drama", {"Bobbie", "Robin"}),
               new Author("Ronnie", "comedy", {"Roberto", "Ron"})};
    std::vector<Book*> parts = {new Book1("Down",  10, 10, 2018, "comedy", 400, "Biggie"),
                                new Book3 ("Up", 10, 10, 2018, "comedy", 470,{{"Ron", 43},{"John", 42},{"Runner",15}})};
    books = {new Book1("Rollercoaster", 27, 11, 2003, "sci-fi",500, "Johny"),
             new Book2("Rollercoaster 2", 27, 1, 2006, "sci-fi", 700, {"Johny", "Robin"}),
             new Book3("Trilling book", 6, 9, 2010, "drama", 670,{{"Ron", 43},{"John", 42},{"Runner",15}}),
             new Book4("Trilling book 2", 6, 9, 2018, "drama", 890,{{"Ron", 58},{"John", 42}}),
             new Book5("UpAndDown", 10, 10, 2018, "comedy", 870, parts)};
    bookModel = new QStringListModel(this);
    QStringList bookList;
    for (const auto& book: books)
        bookList << QString::fromStdString(book->getName());
    authorModel = new QStringListModel(this);
    QStringList authorList;
    for (const auto& author: authors)
        authorList << QString::fromStdString(author->getName());
    bookModel->setStringList(bookList);
    authorModel->setStringList(authorList);

    ui->bookList->setModel(bookModel);
    ui->authorList->setModel(authorModel);
    ui->bookList->setCurrentIndex(bookModel->index(0));
    ui->authorList->setCurrentIndex(authorModel->index(0));
    on_bookList_clicked(bookModel->index(0));
    on_authorList_clicked(authorModel->index(0));
}

MainWindow::~MainWindow(){
    delete ui;
    delete bookModel;
    delete authorModel;
    for (auto& i: authors)
        delete i;
    for (auto& i: books)
        delete i;

}

void MainWindow::on_bookList_clicked(const QModelIndex &index){
    int i = index.row();
    auto authorsList = books[i]->getAuthors();
    std::string allAuthors;
    for (const auto& it: authorsList)
        allAuthors = allAuthors + ", " + it.nick + "(in part: " + it.part->getName() + ", pages: " + std::to_string(it.pages) + ")";
    allAuthors.erase(0, 2);
    ui->BookInfo->setText("<b>Name:</b> " + QString::fromStdString(books[i]->getName()) + "<p><b>Genre: </b>" + QString::fromStdString(books[i]->getGenre())
                          + "<p><b>Type:</b> " + QString::number(books[i]->getType()) + "<p><b>Pages:</b> " + QString::number(books[i]->getSize())
                          + "<p><b>Date:</b> " + QString::number(books[i]->getDay()) + "." + QString::number(books[i]->getMonth())
                          + "." + QString::number(books[i]->getYear()) + "<p><b>All authors:</b> " + QString::fromStdString(allAuthors));
    int j = ui->authorList->currentIndex().row();
    setAuthorInBookInfo(j,i);

}

void MainWindow::on_authorList_clicked(const QModelIndex &index){
    int i = index.row();
    auto nicks = authors[i]->getNicks();
    std::string allNicks;
    for (const auto& it: nicks)
        allNicks = allNicks + ", " + it;
    allNicks.erase(0,2);

    ui->AuthorInfo->setText("<b>Real name:</b> " + QString::fromStdString(authors[i]->getName()) + "<p><b>Genre:</b> " + QString::fromStdString(authors[i]->getGenre())
                            + "<p><b>All nicks:</b> " +  QString::fromStdString(allNicks));
    int j = ui->bookList->currentIndex().row();
    setAuthorInBookInfo(i,j);
}

void MainWindow::setAuthorInBookInfo(int authorRow, int bookRow){
    auto allNicks = authors[authorRow]->getNicks();
    auto allAuthors = books[bookRow]->getAuthors();
    int pages = 0;
    for(const auto& nick: allNicks){
        for(const auto& auth: allAuthors)
            if (nick == auth.nick)
                pages += auth.pages;
    }

    ui->AuthorInBook->setText(QString::fromStdString(authors[authorRow]->getName() + " wrote in " + books[bookRow]->getName()
                                                     + " " + std::to_string(pages) + " pages"));
}

void MainWindow::on_bookList_doubleClicked(const QModelIndex &index){
    sortAuthorsBy(books[index.row()]);
    setAuthorInBookInfo(0,index.row());
    on_authorList_clicked(authorModel->index(0));
}

void MainWindow::sortAuthorsBy(Book *book){
    int counter = 0;
    for (int i = 0; i < authors.size(); i++)
        if (book->contains(*authors[i])){
            std::swap(authors[i], authors[counter]);
            counter++;
        }
    QStringList authorList;
    for (const auto& author: authors)
        authorList << QString::fromStdString(author->getName());
    authorModel->setStringList(authorList);

    ui->authorList->setModel(authorModel);
    ui->authorList->setCurrentIndex(authorModel->index(0));


}

void MainWindow::on_authorList_doubleClicked(const QModelIndex &index){
    sortBooksBy(authors[index.row()]);
    setAuthorInBookInfo(index.row(), 0);
    on_bookList_clicked(bookModel->index(0));
}

void MainWindow::sortBooksBy(Author *author){
    int counter = 0;
    for (int i = 0; i < books.size(); i++)
        if (books[i]->contains(*author)){
            std::swap(books[i], books[counter]);
            counter++;
        }
    QStringList bookList;
    for (const auto& book: books)
        bookList << QString::fromStdString(book->getName());
    authorModel = new QStringListModel(this);

    bookModel->setStringList(bookList);
    ui->bookList->setModel(bookModel);
    ui->bookList->setCurrentIndex(bookModel->index(0));
}
