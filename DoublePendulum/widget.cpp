#include "widget.h"
#include "math.h"
#include <QGraphicsEllipseItem>

Widget::Widget(QWidget *parent)
    : QGraphicsView(parent)
{
    // View properties
    resize(width, height);
    this->setBackgroundBrush(QBrush(Qt::black));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainScene = new QGraphicsScene(this);
    this->setSceneRect(-width / 2, -300, width, height);
    setScene(mainScene);

    mainTimer = new QTimer();
    mainTimer->start(1000/60);
    connect(mainTimer, &QTimer::timeout, this, &Widget::draw);
}

Widget::~Widget()
{
}

void Widget::draw()
{
    // Clean the scene
    mainScene->removeItem(e1);
    delete e1;
    mainScene->removeItem(l1);
    delete l1;
    mainScene->removeItem(e2);
    delete e2;
    mainScene->removeItem(l2);
    delete l2;

    // First pendulum
    float x1 = r1 * sin(a1);
    float y1 = r1 * cos(a1);
    e1 = mainScene->addEllipse(x1 - m1/2, y1 - m1/2, m1, m1, QPen(), QBrush(QColor(255, 192, 203)));
    l1 = mainScene->addLine(0, 0, x1, y1, QPen(QColor(255, 192, 203), 3));

    // Second pendulum
    float x2 = x1 + r2 * sin(a2);
    float y2 = y1 + r2 * cos(a2);
    e2 = mainScene->addEllipse(x2 - m2/2, y2 - m2/2, m2, m2, QPen(), QBrush(QColor(255, 192, 203)));
    l2 = mainScene->addLine(x1, y1, x2, y2, QPen(QColor(255, 192, 203), 3));

    double g = 1;
    float num1 = -g * (2 * m1 + m2) * sin(a1);
    float num2 = -m2 * g * sin(a1 - 2 * a2);
    float num3 = -2 * sin(a1 - a2) * m2;
    float num4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
    float den = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    a1_a = (num1 + num2 + num3 * num4) / den;

    num1 = 2 * sin(a1 - a2);
    num2 = (a1_v * a1_v * r1 * (m1 + m2));
    num3 = g * (m1 + m2) * cos(a1);
    num4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
    den = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
    a2_a = (num1 * (num2 + num3 + num4)) / den;
    a1_v += a1_a;
    a2_v += a2_a;
    a1 += a1_v;
    a2 += a2_v;

    if(framecount > 0){
        mainScene->addLine(pvx, pvy, x2, y2, QPen(Qt::white));
    }
    pvx = x2;
    pvy = y2;
    //a1_v *= 0.99;
    //a2_v *= 0.99;
    framecount++;
}

