#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

class plotter : public QWidget
{
  Q_OBJECT
private:
 // float A, freq, teta;
  bool pressed;
public:
  explicit plotter(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent (QMouseEvent *event);
  //void mouseRelanceEvent(QMouseEvent *event);
signals:
  void mudaxy(int, int);
public slots:

};

#endif // PLOTTER_H
