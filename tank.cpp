//Purpose: Implement Tank class which represents the Tank controlled by player.
//         Class is responsible for defining the position and drawing the image of Tank.
//Author: Nicholas Smith
//Date: 4/4/2013
#include "tank.h"
#include <QSize>

//constructor
Tank::Tank()
{
    size = QSize(30,20);//size is fixed
    position.setX(400);//set the initial position of the tank
    position.setY(550);
    tankimage = new QImage("../space-invaders/images/tank.png");
    //got the image from the web.
}

//moves left only if not touching the left edge
void Tank::moveLeft()
{
    if(position.x() > size.width()/2)
    position.rx()-=5;
}


void Tank::moveRight(int screenWidth)
{//move right only if tank will not touch the right edge
    if(position.x() < (screenWidth-5)-size.width()/2)
    position.rx()+=5;
}

void Tank::setPosition(QPoint newPos)
{
    position = newPos;
}

void Tank::setPosition(int x1, int y1)
{
    position.setX(x1);
    position.setY(y1);
}

QPoint Tank::getPosition()
{
    return position;
}

void Tank::draw(QPainter* painter)
{

    getTankRect();//make sure the rect is updated.
    painter->drawImage(tankRect,*tankimage);//loads the tank image in the rectangle
}

//returns and updates the rectangle for the tank
QRect Tank::getTankRect()
{
    QPoint leftCorner = QPoint(position.x()-size.width()/2,position.y()-size.height()/2);
    tankRect= QRect(leftCorner,size);
    return tankRect;
}

Tank::~Tank()
{
    delete tankimage; //delete QImage object for tank image
}
