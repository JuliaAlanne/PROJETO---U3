#include "plotter.h"


#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

/*plotter::plotter(QWidget *parent) :
  QWidget(parent)
{
  A = 1.0;
  freq = 1.0;
  teta = 0.0;
  startTimer(10); // em ms
}
*/
void plotter::paintEvent(QPaintEvent *event)
{
  int t;
  float y;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  QBrush brush;
  QPen pen;

  pen.setColor(QColor(255,0,0));
  pen.setWidth(1);
  p.setPen(pen);

  brush.setColor(QColor(255,255,227));
  brush.setStyle(Qt::SolidPattern);
  p.setBrush(brush);

  p.drawRect(0,0,width()-1, height()-1);
  p.drawLine(0,height()/2,width(),height()/2);

  pen.setColor(Qt::blue);
  pen.setWidth(1);
  p.setPen(pen);

  // desenho do seno
  int x1, y1, x2, y2;
  x1 = 0;
  y1 = height()/2 - A*std::sin(teta)*height()/2;
  for(x2=1; x2<width(); x2++){
    y2 = height()/2 - A * std::sin(2*3.14*freq*x2/width()
                      + teta)*height()/2;
    p.drawLine(x1,y1,x2,y2);
    x1 = x2;
    y1 = y2;
  }
}

void plotter::timerEvent(QTimerEvent *event)
{
  teta = teta + 0.01;
  if(teta > 2*3.14){
    teta = 0;
  }
  repaint();
}

void plotter::mousePressEvent(QMouseEvent *event)
{
 // qDebug() << event->x() << event->y();
  emit mudaxy(event->x(), event->y());
}

void plotter::mudaAmplitude(int a)
{
  A = a/100.0;
  repaint();
//  A = (float)a/100;
}
