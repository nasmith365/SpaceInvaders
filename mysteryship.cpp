//Purpose: Implements Mysteryship class which represents the ufo/saucer that appears on the top.
//         Class is responsible for defining the position and drawing the image of mysteryship.
//Author: Nicholas Smith
//Date: 4/4/2013

#include "mysteryship.h"
#include <fstream>

#define DEBUG1

MysteryShip::MysteryShip(int direction,int x1, int y1)
{
    position.setX(x1);//set initial position
    position.setY(y1);
    mysteryShipImage = new QImage("../space-invaders/images/UFO.png");
    this->direction = direction;
    size = QSize(30,30);//size of mysteryship is fixed
}

//draw on screen using Mainwindow's painter
void MysteryShip::draw(QPainter* painter)
{
    getMysteryShipRect();//to ensure that the rect is updated to reflect position
    painter->drawImage(mysteryShipRect,*mysteryShipImage);
}

void MysteryShip::move()
{
    if(direction==1)//moving left
        position.rx()-=10;
    else    //moving right
        position.rx()+=10;
}

int MysteryShip::getDirection()
{
    return direction;
}

QPoint MysteryShip::getPosition()
{
    return position;
}


void MysteryShip::setPosition(int x1, int y1)
{
    position.setX(x1);
    position.setY(y1);
}

QRect MysteryShip::getMysteryShipRect()
{
    QPoint topleft = QPoint(position.x()-size.width()/2,position.y()-size.height()/2);
    mysteryShipRect = QRect(topleft,size);
    return mysteryShipRect;
}

bool MysteryShip::checkIfReachedOtherEnd(int screenWidth){
    if (direction==2)//if ship is moving right then reached other end if current position is right corner of screen
    {
        return (position.x()>= screenWidth-size.width()/2) ? true: false;
    }//also consider the size of the mysteryship
    else //if moving left then reached other end if current position is left corner of screen
    {
        return (position.x()<=size.width()/2)?true:false;
    }

}//end of checkIfReachedOtherEnd


MysteryShip::~MysteryShip()
{
    delete mysteryShipImage; //delete the QImage object when ship dies
}
