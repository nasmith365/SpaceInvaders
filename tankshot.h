//Purpose: Define TankShot class which represents the shots thrown by Tank.
//         Class is responsible for defining the position and drawing the image of shots.
//Author: Nicholas Smith
//Date: 4/4/2013
#ifndef TANKSHOT_H
#define TANKSHOT_H

#include <QPoint>
#include <QRect>
#include <QPainter>

class TankShot
{
public:
    TankShot(QPoint initialPosition);//constructor needs the initial position
    void draw(QPainter* painter);
    QPoint getPos();
    void setPos(QPoint point);
    void moveUp();//tankshots only move up
    QRect getTankshotRect();
private:
    QSize size;
    QPoint position;
    QRect tankshotRect;
};

#endif // TANKSHOT_H
