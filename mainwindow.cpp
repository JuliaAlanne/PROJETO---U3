#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLCDNumber>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSliderX,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber,
            SLOT (setNum(int)))
}

MainWindow::~MainWindow()
{
    delete ui;
}

