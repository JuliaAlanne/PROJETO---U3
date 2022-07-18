#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>
#include "sculptor.h"
#include <vector>

class plotter : public QWidget
{
  Q_OBJECT
private:
       // Dimensões do escultor
       int nlinhas, ncolunas, nplanos;
       // Vector 3D que armazena todo o escultor
       QVector<QVector<QVector<Voxel>>> p_sculptor;
       // Plano atual do escultor que eh mostrado na tela
       QVector<QVector<Voxel>> plano_atual;
       // Ponteiro para o escultor
       Sculptor* sculptor;
       // Indices do escultor no momento de um click
       int id_plano, id_linha, id_coluna;
       // Espacamentos entre as linhas do paint
       double h_altura, h_largura;
       // Acao selecionada pelo usuario
       QString action;

       // Caracteristicas da Caixa
       int x_caixa, y_caixa, z_caixa;
       // Caracterisca da Esfera
       int rEsfera;
       // Caracteristica do Elipsoide
       int rXEllipsoid, rYEllipsoid, rZEllipsoid;

       // Cor do desenho
       QColor cor;  bool pressed;
       void ativaV(Voxel &v, QColor cor);
       void desativaV(Voxel &v);

       bool dentroDosLimites(int linha, int coluna, int plano);


public:
  explicit plotter(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent (QMouseEvent *event);
  //void mouseRelanceEvent(QMouseEvent *event);
signals:
  void mudaxy(int, int);
  void alteraSlidersX(int,int);

  void alteraSlidersY(int,int);

  void alteraSlidersZ(int,int);

  void alteraSliderRaioEsfera(int,int);

public slots:
  void abrirDialog();
  void mudaXCaixa();
  void mudaYCaixa();
  void mudaZCaixa();
  void alteraRaioEsfera();
  void alteraRaioXEllipsoid();
  void alteraRaioYEllipsoid();
  void alteraRaioZEllipsoid();



};

#endif // PLOTTER_H
