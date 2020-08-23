//Purpose: Define Tank class which represents the Tank controlled by player.
//         Class is responsible for defining the position and drawing the image of Tank.
//Author: Nicholas Smith
//Date: 4/4/2013
#ifndef TANK_H
#define TANK_H
#include <QPoint>
#include <QPainter>

class Tank
{
private:
    QSize size;
    QPoint position;
    QRect tankRect;//rectangle bounding the tank, useful for finding intersection
    QImage *tankimage;
public:
    Tank();
    ~Tank();
    void setPosition(QPoint newPos);
    void setPosition(int x1, int y1);
    void moveLeft();//moves tank to left
    void moveRight(int screenWidth);//moving tank to right
    QPoint getPosition();
    void draw(QPainter* painter);
    QRect getTankRect();
};

#endif // TANK_H
