#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QLCDNumber>
#include "dialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSliderX,
            SIGNAL(valueChanged(int)),
            ui->labelX,
            SLOT(setNum(int)));
    connect(ui->horizontalSliderY,
            SIGNAL(valueChanged(int)),
            ui->labelY,
            SLOT(setNum(int)));
    connect(ui->horizontalSliderZ,
            SIGNAL(valueChanged(int)),
            ui->labelZ,
            SLOT(setNum(int)));

    connect(ui->actionQuit,
            SIGNAL(triggered()),
            this,
            SLOT(finalizaprograma()));
    connect(ui->horizontalSliderX,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber_BoxX,
            SLOT(mudaXCaixa(int)));

    connect(ui->horizontalSliderY,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber_BoxY,
            SLOT(mudaYCaixa(int)));

    connect(ui->horizontalSliderZ,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber_BoxZ,
            SLOT(mudaZCaixa(int)));

    connect(ui->actionSave,
            SIGNAL(triggered()),
            this,
            SLOT(salvaArquivo()));

    connect(ui->horizontalSliderEsferaR,
            SIGNAL(valueChanged(int)),
            ui->widget,
            SLOT(alteraRaioEsfera(int)));

    // Alterando os valor dos raio do elipsoide
    connect(ui->horizontalSliderRXellipsoid,
            SIGNAL(valueChanged(int)),
            ui->widget,
            SLOT(alteraRaioXEllipsoid(int)));

    connect(ui->horizontalSliderRYellipsoid,
            SIGNAL(valueChanged(int)),
            ui->widget,
            SLOT(alteraRaioYEllipsoid(int)));

    connect(ui->horizontalSliderRZellipsoid,
            SIGNAL(valueChanged(int)),
            ui->widget,
            SLOT(alteraRaioZEllipsoid(int)));


    connect(ui->actionNovoDesenho,
            SIGNAL(triggered()),
            this,
            SLOT(novoDesenho()));

}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::finalizaprograma(){
  exit(1);
}
void MainWindow::salvaArquivo(){
  QFileDialog dialog;
  QString selectedFilter;
  QString filename =
      dialog.getSaveFileName(this,tr("Salvar"),
                             QDir::currentPath(),
                             tr("Arquivo OFF(*.off);;Arquivo OFF2(*.off2)"),
                             &selectedFilter);
  if(filename.isNull()){
    return;
  }
  if(selectedFilter == "Arquivo OFF(*.off)"){
    // grava o arquivo
    // escultor->writeOFF(filename.toStdString());
  }
}


void MainWindow::on_actionsalvaarquivo_triggered()
{

}

