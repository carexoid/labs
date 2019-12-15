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
             new Book2 ("Rollercoaster2", 27, 1, 2006, "sci-fi", 700, {"Johny", "Robin"}),
             new Book3 ("Trilling book", 6, 9, 2010, "drama", 670,{{"Ron", 43},{"John", 42},{"Runner",15}}),
             new Book4 ("Trilling book2", 6, 9, 2018, "drama", 890,{{"Ron", 58},{"John", 42}}),
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



}

MainWindow::~MainWindow()
{
    delete ui;
    delete bookModel;
    delete authorModel;
    for (auto& i: authors)
        delete i;
    for (auto& i: books)
        delete i;

}

void MainWindow::on_bookList_clicked(const QModelIndex &index)
{
    int i = index.row();
    ui->BookInfo->setText("Name: " + QString::fromStdString(books[i]->getName()) + "\nGenre: " + QString::fromStdString(books[i]->getGenre())
                            + "\nType: " + QString::number(books[i]->getType()) + "\nPages: " + QString::number(books[i]->getSize()));
}
