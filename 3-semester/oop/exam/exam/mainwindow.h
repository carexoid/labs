#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <vector>
#include <string>
#include <iostream>
#include "book.h"
#include "author.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bookList_clicked(const QModelIndex &index);

    void on_authorList_clicked(const QModelIndex &index);

    void on_bookList_doubleClicked(const QModelIndex &index);

    void on_authorList_doubleClicked(const QModelIndex &index);

    void on_reseter_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Book*> books;
    std::vector<Author*> authors;
    QStringListModel *bookModel;
    QStringListModel *authorModel;

    void setAuthorInBookInfo(int authorRow, int bookRow);

    void sortAuthorsBy(Book* book);

    void sortBooksBy(Author* author);

    void resetFilters();
};

#endif // MAINWINDOW_H
