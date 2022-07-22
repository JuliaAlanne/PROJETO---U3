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

    connect(ui->actionEscultor,
            SIGNAL(triggered(bool)),
            ui->widget,
            SLOT(abrirDialog()));
    connect(ui->actionQuit,
            SIGNAL(triggered()),
            this,
            SLOT(finalizaprograma()));

    connect(ui->horizontalSliderX,
            SIGNAL(valueChanged(int)),
            ui->lcdNumber_BoxX,
            SLOT(setNum(int)));

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
    connect(ui->widget,
                SIGNAL(alteraSlidersX(int,int)),
                ui->horizontalSliderRXellipsoid,
                SLOT(setRange(int,int)));

        connect(ui->widget,
                SIGNAL(alteraSlidersX(int,int)),
                ui->horizontalSliderX,
                SLOT(setRange(int,int)));

        // Eixo Y
        /*connect(ui->widget,
                SIGNAL(alteraSlidersY(int,int)),
                ui->horizontalY,
                SLOT(setRange(int,int)));*/

        connect(ui->widget,
                SIGNAL(alteraSlidersY(int,int)),
                ui->horizontalSliderRYellipsoid,
                SLOT(setRange(int,int)));

        connect(ui->widget,
                SIGNAL(alteraSlidersY(int,int)),
                ui->horizontalSliderY,
                SLOT(setRange(int,int)));

        // Eixo Z
        connect(ui->widget,
                SIGNAL(alteraSlidersZ(int,int)),
                ui->horizontalSliderZ,
                SLOT(setRange(int,int)));

        connect(ui->widget,
                SIGNAL(alteraSlidersZ(int,int)),
                ui->horizontalSliderRZellipsoid,
                SLOT(setRange(int,int)));

        connect(ui->widget,
                SIGNAL(alteraSlidersZ(int,int)),
                ui->horizontalSliderXY,
                SLOT(setRange(int,int)));

        // Raio da Esfera
        connect(ui->widget,
                SIGNAL(alteraSliderRaioEsfera(int,int)),
                ui->horizontalSliderEsferaR,
                SLOT(setRange(int,int)));

        // Mudando o plano que é mostrado na tela (Eixo Z)
        connect(ui->horizontalSliderXY,
                SIGNAL(valueChanged(int)),
                ui->widget,
                SLOT(mudaPlanoZ(int)));
        connect(this,
                SIGNAL(nomeAcao(QString)),
                ui->widget,
                SLOT(acaoSelecionada(QString)));

        // Alterando os valores das dimensões da caixa
        connect(ui->horizontalSliderX,
                SIGNAL(valueChanged(int)),
                ui->widget,
                SLOT(mudaXCaixa(int)));

        connect(ui->horizontalSliderY,
                SIGNAL(valueChanged(int)),
                ui->widget,
                SLOT(mudaYCaixa(int)));

        connect(ui->horizontalSliderZ,
                SIGNAL(valueChanged(int)),
                ui->widget,
                SLOT(mudaZCaixa(int)));

        // Alterando o valor do raio da esfera
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

      // Alterando os valores RGB
        connect(ui->widget,
                SIGNAL(alteraSliderR(int)),
                ui->horizontalR,
                SLOT(setValue(int)));

        connect(ui->widget,
                SIGNAL(alteraSliderG(int)),
                ui->horizontalG,
                SLOT(setValue(int)));

        connect(ui->widget,
                SIGNAL(alteraSliderB(int)),
                ui->horizontalB,
                SLOT(setValue(int)));




        ultimaAcao = "";




    connect(ui->actionEscultor_2,
            SIGNAL(triggered(bool)),
            ui->widget,
            SLOT(abrirDialog()));

}



MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::finalizaprograma(){
  exit(1);
}*/
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




void MainWindow::capturaAcao(bool checked)
{
    if (ultimaAcao.compare(ui->actionPutVoxel->text()) == 0){
        ui->actionPutVoxel->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionCutVoxel->text()) == 0) {
        ui->actionCutVoxel->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionPutBox->text()) == 0) {
        ui->actionPutBox->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionCutBox->text()) == 0) {
        ui->actionCutBox->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionPutSphere->text()) == 0) {
        ui->actionPutSphere->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionCutSphere->text()) == 0) {
        ui->actionCutSphere->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionPutEllipsoid->text()) == 0) {
        ui->actionPutEllipsoid->setChecked(false);
    }
    else if (ultimaAcao.compare(ui->actionCutEllipsoid->text()) == 0) {
        ui->actionCutEllipsoid->setChecked(false);
    }


    if(ui->actionPutVoxel->isChecked()){
        qDebug() << ui->actionPutVoxel->text();
        emit nomeAcao(ui->actionPutVoxel->text());
        ultimaAcao = ui->actionPutVoxel->text();
    }
    else if (ui->actionCutVoxel->isChecked()) {
        qDebug() << ui->actionCutVoxel->text();
        emit nomeAcao(ui->actionCutVoxel->text());
        ultimaAcao = ui->actionCutVoxel->text();
    }
    else if (ui->actionPutBox->isChecked()) {
        qDebug() << ui->actionPutBox->text();
        emit nomeAcao(ui->actionPutBox->text());
        ultimaAcao = ui->actionPutBox->text();
    }
    else if (ui->actionCutBox->isChecked()) {
        qDebug() << ui->actionCutBox->text();
        emit nomeAcao(ui->actionCutBox->text());
        ultimaAcao = ui->actionCutBox->text();
    }
    else if (ui->actionPutSphere->isChecked()) {
        qDebug() << ui->actionPutSphere->text();
        emit nomeAcao(ui->actionPutSphere->text());
        ultimaAcao = ui->actionPutSphere->text();
    }
    else if (ui->actionCutSphere->isChecked()) {
        qDebug() << ui->actionCutSphere->text();
        emit nomeAcao(ui->actionCutSphere->text());
        ultimaAcao = ui->actionCutSphere->text();
    }
    else if (ui->actionPutEllipsoid->isChecked()) {
        qDebug() << ui->actionPutEllipsoid->text();
        emit nomeAcao(ui->actionPutEllipsoid->text());
        ultimaAcao = ui->actionPutEllipsoid->text();
    }
    else if (ui->actionCutEllipsoid->isChecked()) {
        qDebug() << ui->actionCutEllipsoid->text();
        emit nomeAcao(ui->actionCutEllipsoid->text());
        ultimaAcao = ui->actionCutEllipsoid->text();
    }
}

