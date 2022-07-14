#include "plotter.h"

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

plotter::plotter(QWidget *parent) :
  QWidget(parent){


  //nl=nc=np=0
  pressed= false;
  //setMouseTracking(true);

}

void plotter::paintEvent(QPaintEvent *event)
{
  float x,y;

  QPainter p(this);
  QBrush brush;
  QPen pen;

  p.setRenderHint(QPainter::Antialiasing);

  pen.setColor(QColor(255,0,0));
 // pen.setStyle(Qt::SolidPattern);
  pen.setWidth(1);

  pen.setColor(QColor(0,0,0));
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(3);

  p.setPen(pen);
  p.setBrush(brush);
  p.drawRect(0,0,width(),height());




}


void plotter::mousePressEvent(QMouseEvent *event)
{
  if(event->button() == Qt::LeftButton){
       pressed = true;
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
