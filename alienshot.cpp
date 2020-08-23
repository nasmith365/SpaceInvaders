//Purpose: Define AlienShot class which represents the shots thrown by aliens.
//         Class is responsible for defining the position and drawing the image of shots.
//Authors:Nicholas Smith
//Date: 4/4/2013

#include "alienshot.h"

//create static objects, that can be destroyed by calling the deleteImages() function
QImage* AlienShot::alienshotImage1 = new QImage("../space-invaders/images/torpedo.png");
QImage* AlienShot::alienshotImage2 = new QImage("../space-invaders/images/ship.png");
QImage* AlienShot::alienshotImage3 = new QImage("../space-invaders/images/needle.png");

//Constructor
AlienShot::AlienShot(int shotType, QPoint pos)
{
    size = QSize(10,20);//size of all shots is fixed
    type=shotType;
    position = pos;
}

//draw is responsible for displaying the object, given the painter object
void AlienShot::draw(QPainter* painter)
{
    getAlienshotRect();//update AlienshotRect
    if (type==0)
        painter->drawImage(AlienshotRect,*alienshotImage1);//draw the image in the rectangle
    else if (type==1)
        painter->drawImage(AlienshotRect,*alienshotImage2);
    else
        painter->drawImage(AlienshotRect,*alienshotImage3);

}//end of draw

QPoint AlienShot::getPosition()
{
    return position;
}


void AlienShot::setPosition(QPoint point)
{
    position = point;
}

void AlienShot::moveDown()
{
    position.ry()+=15;
}

//updates and returns the rectangle bounding the alienshot
QRect AlienShot::getAlienshotRect()
{
    QPoint topleft = QPoint(position.x()-size.width()/2,position.y()-size.height()/2);
    AlienshotRect = QRect(topleft,size);
    return AlienshotRect ;
}

//function to be called in destructor of mainwindow
void AlienShot::deleteImages()
{
    delete alienshotImage1;
    delete alienshotImage2;
    delete alienshotImage3;
}
