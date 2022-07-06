#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

class plotter : public QWidget
{
  Q_OBJECT
private:
  float A, freq, teta;
public:
  explicit plotter(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseRelanceEvent(QMouseEvent *event);
signals:
  void mudaxy(int, int);
public slots:
  void mudaAmplitude(int a);
};

#endif // PLOTTER_H
