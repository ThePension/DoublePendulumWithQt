#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QtMath>

class Widget : public QGraphicsView
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int width = 1000, height = 800;

    QGraphicsScene * mainScene = nullptr;

    QTimer * mainTimer;

    double r1 = 200, r2 = 200, m1 = 30, m2 = 30, a1 = 90, a2 = 45;
    double a1_v = 0, a2_v = 0;
    double a1_a = 0, a2_a = 0;
    double pvx, pvy;
    int framecount = 0;
    QGraphicsEllipseItem * e1 = nullptr, * e2 = nullptr;
    QGraphicsLineItem * l1 = nullptr, *l2 = nullptr;

public slots:
    void draw();
};
#endif // WIDGET_H
