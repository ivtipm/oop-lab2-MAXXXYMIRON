#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <QKeyEvent>
#include<QMessageBox>
#include "Expression.h"
#include "parser.h"
#include "history.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Off_clicked();

    void keyPressEvent(QKeyEvent *event);

    void on_Equal_clicked();

    void on_History_clicked();


    void addDigit();

    void addBehindOperations();

    void addPoint();

    void addInFrontOperation();

    void addBracket();

    void drop();

    void backspace();

    void Changed();

private:
    Ui::MainWindow *ui;
    Expression expres;
    Parser parser;
    History hist;
    bool open = false;
};
#endif // MAINWINDOW_H
