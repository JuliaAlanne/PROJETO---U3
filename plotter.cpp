#include "plotter.h"
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QDebug>
#include<QMessageBox>
#include <QColor>
#include <math.h>
#include <algorithm>
#include <QMouseEvent>
#include<QFileDialog>
#include<cstring>
#include <QColorDialog>


#include "dialog.h"



plotter::plotter(QWidget *parent) : QWidget(parent)
{
    // Dimensões do Escultor
    nlinhas = ncolunas = nplanos = 0;
    // Instanciando um escultor zerado
    sculptor = new Sculptor(nlinhas,ncolunas,nplanos);
    // Indices do escultor no momento de um click
    id_plano = id_linha = id_coluna = 0;
    // Espacamentos entre as linhas do paint
    h_largura = h_altura = 0;
    // Acao Selecionada
    action = " ";
    // Caraceristicas da Caixa
    x_caixa = y_caixa = z_caixa = 0;
    // Caracteristica da Esfera
    rEsfera = 0;
    // Caracteristica do Elipsoide
    rXEllipsoid = rYEllipsoid = rZEllipsoid = 0;
    // Cor do desenho
    cor = QColor(0,0,0,255);

}


void plotter::paintEvent(QPaintEvent *event)
{
  //float x,y;

  QPainter p(this);
  QBrush brush;
  QPen pen;

  p.setRenderHint(QPainter::Antialiasing);

  brush.setColor(QColor(255,255,255));
  brush.setStyle(Qt::SolidPattern);

  //area de desenho
  pen.setColor(QColor(255,0,0));
  //pen.setStyle(Qt::SolidPattern);
  pen.setWidth(1);

  pen.setColor(QColor(0,0,0));
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(3);

  p.setPen(pen);
  p.setBrush(brush);
  p.drawRect(0,0,width(),height());
  brush.setColor(QColor(0,0,0));

  p.setBrush(brush);
  for (int i=0;i<nlinhas;i++) {
      for(int j=0; j<ncolunas; j++){
          if (plano_atual[i][j].isOn == true){
              qDebug() << "entrou";
              int pos_linha = i*h_altura;
              int pos_coluna = j*h_largura;

              brush.setColor(QColor(211, 215, 207));
              p.setBrush(brush);
              p.drawRect(pos_coluna,pos_linha,h_largura,h_altura);

              Voxel aux = plano_atual[i][j];
              brush.setColor(QColor(aux.r,aux.g,aux.b,aux.a));
              p.setBrush(brush);
              p.drawEllipse(pos_coluna,pos_linha,h_largura,h_altura);
          }
      }

  }



}


void plotter::mousePressEvent(QMouseEvent *event)
{
    if(nlinhas !=0 && ncolunas !=0 && nplanos !=0){
           if(event->button() == Qt::LeftButton){


               int pos_coluna = event-> x();
               int pos_linha =  event-> y();

               // Posição na Vector
               id_linha = pos_linha/h_altura;
               id_coluna = pos_coluna/h_largura;

               // cor(0,0,0,255);

               sculptor->setColor(cor.red()/255.0f,cor.green()/255.0f,cor.blue()/255.0f,cor.alpha()/255.0f);

               if(action.compare("PutVoxel",Qt::CaseInsensitive) == 0){
                   if (dentroDosLimites(id_linha,id_coluna,id_plano)){
                       ativaV(p_sculptor[id_plano][id_linha][id_coluna],cor);
                       sculptor->putVoxel(id_linha,id_coluna,id_plano);
                   }
                   //sculptor->print_sculptor();
               }

               else if (action.compare("CutVoxel",Qt::CaseInsensitive) == 0) {
                   if (dentroDosLimites(id_linha,id_coluna,id_plano)){
                       desativaV(p_sculptor[id_plano][id_linha][id_coluna]);
                       sculptor->cutVoxel(id_linha,id_coluna,id_plano);
                   }
               }
               else if (action.compare("PutBox",Qt::CaseInsensitive) == 0) {
                   for(int k=0; k<z_caixa;k++){
                       for(int i=0;i<x_caixa;i++){
                           for(int j=0; j<y_caixa;j++){
                               if (dentroDosLimites(id_linha+i,id_coluna+j,id_plano+k)){
                                   ativaV(p_sculptor[id_plano+k][id_linha+i][id_coluna+j],cor);
                                   sculptor->putVoxel(id_linha+i,id_coluna+j,id_plano+k);
                               }
                           }
                       }
                   }
               }

               else if (action.compare("CutBox",Qt::CaseInsensitive) == 0) {
                   for(int k=0; k<z_caixa;k++){
                       for(int i=0;i<x_caixa;i++){
                           for(int j=0; j<y_caixa;j++){
                               if (dentroDosLimites(id_linha+i,id_coluna+j,id_plano+k)){
                                   desativaV(p_sculptor[id_plano+k][id_linha+i][id_coluna+j]);
                                   sculptor->cutVoxel(id_linha+i,id_coluna+j,id_plano+k);
                               }
                           }
                       }
                   }
               }

               else if (action.compare("PutSphere",Qt::CaseInsensitive) == 0) {
                   double dist;
                   for(int k=id_plano - rEsfera; k<=id_plano + rEsfera; k++){
                       for (int i=id_linha - rEsfera; i<=id_linha + rEsfera; i++) {
                           for (int j=id_coluna - rEsfera; j<=id_coluna + rEsfera; j++){
                              dist = pow(i-id_linha,2) + pow(j-id_coluna,2) + pow(k-id_plano,2);
                              if (dist <= pow(rEsfera,2)){
                                  if (dentroDosLimites(i,j,k)){
                                      ativaV(p_sculptor[k][i][j],cor);
                                      sculptor->putVoxel(i,j,k);
                                  }
                              }
                           }
                       }
                   }
               }

               else if (action.compare("CutSphere",Qt::CaseInsensitive) == 0) {
                   double dist;
                   for(int k=id_plano - rEsfera; k<=id_plano + rEsfera; k++){
                       for (int i=id_linha - rEsfera; i<=id_linha + rEsfera; i++) {
                           for (int j=id_coluna - rEsfera; j<=id_coluna + rEsfera; j++){
                              dist = pow(i-id_linha,2) + pow(j-id_coluna,2) + pow(k-id_plano,2);
                              if (dist <= pow(rEsfera,2)){
                                  if (dentroDosLimites(i,j,k)){
                                      desativaV(p_sculptor[k][i][j]);
                                      sculptor->cutVoxel(i,j,k);
                                  }
                              }
                           }
                       }
                   }
               }

               else if (action.compare("PutEllipsoid", Qt::CaseInsensitive)==0) {
                   double dist;

                   if (rXEllipsoid ==0){
                       for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                               dist =  pow(j-id_coluna,2)/pow(rYEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(id_linha,j,k)){
                                       ativaV(p_sculptor[k][id_linha][j],cor);
                                       sculptor->putVoxel(id_linha,j,k);
                                   }
                                   //t.putVoxel(id_linha,j,k);
                             }
                           }
                       }
                   }

                   else if(rYEllipsoid==0){
                       for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                           for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                               dist =  pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,id_coluna,k)){
                                       ativaV(p_sculptor[k][i][id_coluna],cor);
                                       sculptor->putVoxel(i,id_coluna,k);
                                   }
                                   //t.putVoxel(i,id_coluna,k);
                             }
                           }
                       }
                   }
                   else if (rZEllipsoid==0) {
                       for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                               dist =  pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(j-id_coluna,2)/pow(rYEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,j,id_plano)){
                                       ativaV(p_sculptor[id_plano][i][j],cor);
                                       sculptor->putVoxel(i,j,id_plano);
                                   }
                                   //t.putVoxel(i,j,id_plano);
                             }
                           }
                       }
                   }
                   else{
                   for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                       for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                                 dist = pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(j-id_coluna,2)/pow(rYEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,j,k)){
                                       ativaV(p_sculptor[k][i][j],cor);
                                       sculptor->putVoxel(i,j,k);
                                   }
                                   //t.putVoxel(i,j,k);
                               }

                           }

                       }
                    }
                 }


               }

               else if (action.compare("CutEllipsoid", Qt::CaseInsensitive)==0) {
                   double dist;

                   if (rXEllipsoid ==0){
                       for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                               dist =  pow(j-id_coluna,2)/pow(rYEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(id_linha,j,k)){
                                       desativaV(p_sculptor[k][id_linha][j]);
                                       sculptor->cutVoxel(id_linha,j,k);
                                   }
                                   //t.putVoxel(id_linha,j,k);
                             }
                           }
                       }
                   }

                   else if(rYEllipsoid==0){
                       for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                           for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                               dist =  pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,id_coluna,k)){
                                       desativaV(p_sculptor[k][i][id_coluna]);
                                       sculptor->cutVoxel(i,id_coluna,k);
                                   }
                                   //t.putVoxel(i,id_coluna,k);
                             }
                           }
                       }
                   }
                   else if (rZEllipsoid==0) {
                       for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                               dist =  pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(j-id_coluna,2)/pow(rYEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,j,id_plano)){
                                       desativaV(p_sculptor[id_plano][i][j]);
                                       sculptor->cutVoxel(i,j,id_plano);
                                   }
                                   //t.putVoxel(i,j,id_plano);
                             }
                           }
                       }
                   }
                   else{
                   for (int k=id_plano - rZEllipsoid;k<=id_plano + rZEllipsoid;k++) {
                       for (int i=id_linha - rXEllipsoid;i<=id_linha + rXEllipsoid;i++) {
                           for (int j=id_coluna - rYEllipsoid;j<=id_coluna + rYEllipsoid;j++) {
                                 dist = pow(i-id_linha,2)/pow(rXEllipsoid,2) + pow(j-id_coluna,2)/pow(rYEllipsoid,2) + pow(k-id_plano,2)/pow(rZEllipsoid,2);
                               if(dist<=1){
                                   if (dentroDosLimites(i,j,k)){
                                       desativaV(p_sculptor[k][i][j]);
                                       sculptor->cutVoxel(i,j,k);
                                   }
                                   //t.putVoxel(i,j,k);
                               }

                           }

                       }
                    }
                 }

               }



               qDebug() << "Pos Plano: " << id_plano;
               qDebug() << "Pos Linha: " << id_linha;
               qDebug() << "Pos Coluna: " << id_coluna;

               plano_atual = p_sculptor[id_plano];
               repaint();

           }
       }

}
void plotter::mouseMoveEvent(QMouseEvent *event)
{
  if(pressed){
    emit mudaxy(event->x(), event->y());
  }
}


/*void plotter::mouseReleaseEvent(QMouseEvent *event)
{
  pressed = false;
}*/
void plotter::abrirDialog()
{
    Dialog e;
    if(e.exec() == QDialog::Accepted){
        // Pegando as dimensões do escultor
        nlinhas = e.getNumLinhas();
        ncolunas = e.getNumColunas();
        nplanos = e.getNumPlanos();
        if(nlinhas !=0 && ncolunas !=0 && nplanos !=0){
            // Voxel com todas as proprieades iguais a zero
            Voxel voxel_zero;
            voxel_zero.r = voxel_zero.b = voxel_zero.g = 0;
            voxel_zero.a = 0.0f;
            voxel_zero.isOn = false;

            p_sculptor.clear();
            // Craindo o escultor 3D com Voxels zerados
            for (int k=0;k<nplanos;k++) {
                    QVector<QVector<Voxel>> aux1;
                for(int i=0;i<nlinhas; i++){
                    QVector<Voxel> aux2;
                    for(int j=0;j<ncolunas; j++){
                        aux2.push_back(voxel_zero);
                    }
                    aux1.push_back(aux2);
                }
                p_sculptor.push_back(aux1);
            }

            // Definido como a primeira tela de desenho o plano zero(XY)
            plano_atual = p_sculptor[0];

            // Removendo o escultor anterior anterior
            delete sculptor;
            // Instanciando o escultor atual
            sculptor = new Sculptor(nlinhas,ncolunas,nplanos);
            sculptor-> print_sculptor();

            // Redefinindo as propriedades dos sliders (emitindo sinais para mainwindow)
            emit alteraSlidersX(0,nlinhas-1);
            emit alteraSlidersY(0,ncolunas-1);
            emit alteraSlidersZ(0,nplanos-1);

            int re[] = {nlinhas-1,nplanos-1,ncolunas-1};
            emit alteraSliderRaioEsfera(0,*std::min_element(re,re+3));

            qDebug() << "Num Linhas: " << nlinhas;
            qDebug() << "Num Colunas: " << ncolunas;
            qDebug() << "Num Planos: " << nplanos;

            repaint();
            }
        else {
            nlinhas = nplanos = ncolunas = 0;
            QMessageBox box;
            box.setText("Dimensoes Invalidas: Todas as dimensoes devem ser diferentes de zero!!");
            box.exec();
        }
    }
}
void plotter::acaoSelec(QString _action)
{
    action = _action;
    qDebug() << "Acao Selecionada " << action;
}

void plotter::mudaXCaixa(int _x)
{
    x_caixa = _x;
}

void plotter::mudaYCaixa(int _y)
{
    y_caixa = _y;
}

void plotter::mudaZCaixa(int _z)
{
    z_caixa = _z;
}

void plotter::alteraRaioEsfera(int _re)
{
    rEsfera = _re;
}

void plotter::alteraRaioXEllipsoid(int _rx)
{
    rXEllipsoid = _rx;
}

void plotter::alteraRaioYEllipsoid(int _ry)
{
    rYEllipsoid = _ry;
}

void plotter::alteraRaioZEllipsoid(int _rz)
{
    rZEllipsoid = _rz;
}
void plotter::alteraCor()
{
    QColor c;
    QColorDialog dColor;
    dColor.exec();
    c = dColor.selectedColor();

    // Atualizando a cor
    cor.setRed(c.red());
    cor.setGreen(c.green());
    cor.setBlue(c.blue());
    cor.setAlpha(255);

    //Atualizando os Sliders das Cores
    emit alteraSliderR(c.red());
    emit alteraSliderG(c.green());
    emit alteraSliderB(c.blue());




}
void plotter::alteraR(int _r)
{
    cor.setRed(_r);
}

void plotter::alteraB(int _b)
{
    cor.setBlue(_b);
}

void plotter::alteraG(int _g)
{
    cor.setGreen(_g);
}

void plotter::salvar()
{
  if (nlinhas != 0 && ncolunas !=0 && nplanos !=0){
   QString fileName = QFileDialog::getSaveFileName(this, tr("Salve o Escultor em formato .off"),"",tr("(*.off);;All Files (*)"));
   if (fileName.compare("")){
    sculptor-> writeOFF(fileName.toStdString());
   }
  }
  else {
      QMessageBox box;
      box.setText("O Escultor está vazio, não é possível salvar o arquivo .off");
      box.exec();
  }

}

void plotter::ativaV(Voxel &v, QColor cor)
{
    v.isOn = true;
    v.r = cor.red();
    v.g = cor.green();
    v.b = cor.blue();
    v.a = cor.alpha();
}

void plotter::desativaV(Voxel &v)
{
    v.isOn = false;
}

bool plotter::dentroDosLimites(int linha, int coluna, int plano)
{
    if ((plano < nplanos && plano >= 0) && (linha < nlinhas && linha >= 0) && (coluna < ncolunas && coluna >=0)){
        return true;
    }

    return false;
}
