#include "CalculatorWindow.h"
#include "ui_CalculatorWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->Hist->setVisible(open);


    connect(ui->Zero, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->One, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Two, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Three, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Four, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Five, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Six, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Seven, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Eight, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Nine, SIGNAL(clicked()), this, SLOT(addDigit()));
    connect(ui->Point, SIGNAL(clicked()), this, SLOT(addPoint()));


    connect(ui->Add, SIGNAL(clicked()), this, SLOT(addBehindOperations()));
    connect(ui->Sub, SIGNAL(clicked()), this, SLOT(addBehindOperations()));
    connect(ui->Mul, SIGNAL(clicked()), this, SLOT(addBehindOperations()));
    connect(ui->Div, SIGNAL(clicked()), this, SLOT(addBehindOperations()));
    connect(ui->Pow, SIGNAL(clicked()), this, SLOT(addBehindOperations()));


    connect(ui->Sqrt, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));
    connect(ui->Sin, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));
    connect(ui->Cos, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));
    connect(ui->Tan, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));
    connect(ui->Ln, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));
    connect(ui->Exp, SIGNAL(clicked()), this, SLOT(addInFrontOperation()));


    connect(ui->OpenBraket, SIGNAL(clicked()), this, SLOT(addBracket()));
    connect(ui->CloseBraket, SIGNAL(clicked()), this, SLOT(addBracket()));


    connect(ui->Drop, SIGNAL(clicked()), this, SLOT(drop()));
    connect(ui->Backspace, SIGNAL(clicked()), this, SLOT(backspace()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addDigit()
{
    QPushButton *button = (QPushButton *)sender();
    expres.AddDigit(button->text().toStdString()[0]);
    Changed();
}

void MainWindow::addBehindOperations()
{
    QPushButton *button = (QPushButton *)sender();
    expres.AddBehindOperations(button->text().toStdString()[0]);
    Changed();
}

void MainWindow::addPoint()
{
    expres.AddPoint();
    Changed();
}

void MainWindow::addInFrontOperation()
{
    QPushButton *button = (QPushButton *)sender();
    expres.AddInFrontOperation(button->text().toStdString());
    Changed();
}

void MainWindow::addBracket()
{
    QPushButton *button = (QPushButton *)sender();
    expres.AddBracket(button->text().toStdString()[0]);
    Changed();
}

void MainWindow::drop()
{
    expres.Drop();
    Changed();
}

void MainWindow::backspace()
{
    expres.Backspace();
    Changed();
}

void MainWindow::Changed()
{
    ui->Expression->setText(QString::fromStdString(expres.GetExpression()));
}


void MainWindow::on_Off_clicked()
{
    close();
}

void MainWindow::on_Equal_clicked()
{
    if(!expres.RightExpression()) return;

    hist.WriteHist(expres.GetExpression());
    expres.SetExpression(parser.ParsingExpression(expres.GetExpression()));
    hist.WriteHist("= " + expres.GetExpression());
    Changed();
}

void MainWindow::on_History_clicked()
{
    try
    {
        vector<string> h = hist.GetHistory();
        ui->Hist->setPlainText("");
        open = !open;
        ui->Hist->setVisible(open);
        for(unsigned i = 0; i < h.size(); i++)
        {
            ui->Hist->appendPlainText(QString::fromStdString(h[i]));
        }
    }
    catch (History::ERRORS e)
    {
        QMessageBox::warning(this, "Внимание", "История вычислений пуста");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        on_Off_clicked();
        break;
    case Qt::Key_Backspace:
        ui->Backspace->clicked();
        break;
    case Qt::Key_Plus:
        ui->Add->clicked();
        break;
    case Qt::Key_Minus:
        ui->Sub->clicked();;
        break;
    case Qt::Key_Asterisk:
        ui->Mul->clicked();
        break;
    case Qt::Key_Slash:
        ui->Div->clicked();
        break;
    case Qt::Key_AsciiCircum:
        ui->Pow->clicked();
        break;
    case Qt::Key_0:
        ui->Zero->clicked();
        break;
    case Qt::Key_1:
        ui->One->clicked();
        break;
    case Qt::Key_2:
        ui->Two->clicked();
        break;
    case Qt::Key_3:
        ui->Three->clicked();
        break;
    case Qt::Key_4:
        ui->Four->clicked();
        break;
    case Qt::Key_5:
        ui->Five->clicked();
        break;
    case Qt::Key_6:
        ui->Six->clicked();
        break;
    case Qt::Key_7:
        ui->Seven->clicked();
        break;
    case Qt::Key_8:
        ui->Eight->clicked();
        break;
    case Qt::Key_9:
        ui->Nine->clicked();
        break;
    case Qt::Key_Period:
        ui->Point->clicked();
        break;
    case Qt::Key_Q:
        ui->Sqrt->clicked();
        break;
    case Qt::Key_S:
        ui->Sin->clicked();
        break;
    case Qt::Key_C:
        ui->Cos->clicked();
        break;
    case Qt::Key_T:
        ui->Tan->clicked();
        break;
    case Qt::Key_L:
        ui->Ln->clicked();
        break;
    case Qt::Key_E:
        ui->Exp->clicked();
        break;
    case Qt::Key_ParenLeft:
        ui->OpenBraket->clicked();
        break;
    case Qt::Key_ParenRight:
        ui->CloseBraket->clicked();
        break;
    case Qt::Key_End:
        ui->Drop->clicked();
        break;
    case Qt::Key_Enter:
        on_Equal_clicked();
        break;
    case Qt::Key_H:
        on_History_clicked();
        break;
    }
}
