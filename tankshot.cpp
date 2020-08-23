//Purpose: Implement TankShot class which represents the shots thrown by Tank.
//         Class is responsible for defining the position and drawing the image of shots.
//Author: Nicholas Smith
//Date: 4/4/2013
#include "tankshot.h"

TankShot::TankShot(QPoint initialPosition)
{
    position = initialPosition;
    size = QSize(4,4);//size is fixed
}

void TankShot::moveUp()
{
    position.ry()-=10;
}

void TankShot::draw(QPainter* painter)
{
    painter->drawEllipse(getTankshotRect());//just a circle is good for shots :)
}

QPoint TankShot::getPos()
{
    return position;
}

void TankShot::setPos(QPoint point)
{
    position = point;
}

//return and update the rectangle bounding the tankshot
QRect TankShot::getTankshotRect()
{
    QPoint topleft = QPoint(position.x()-size.width()/2,position.y()-size.height()/2);
    tankshotRect = QRect(topleft,size);
    return tankshotRect;
}

