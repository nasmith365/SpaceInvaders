//Purpose: The Alien class contains and offers all of information associated with an alien.
//	   It also places aliens and controls which type of alien image will be displayed in a particular spot.
//Authors:Nicholas Smith
//Date: 4/4/2013

#include "alien.h"
#include <cstdlib>
#include <QPainter>

//int Alien::alienDirectionIndicator=0; //initialize the static variable to 0, in beginning
QImage* Alien::alienImage1 = new QImage("../space-invaders/images/invader1.jpg");
QImage* Alien::alienImage2 = new QImage("../space-invaders/images/invader2.jpg");
QImage* Alien::alienImage3 = new QImage("../space-invaders/images/invader3.jpg");
QSize Alien::sizeOfAlien = QSize(30,30);



//Alien::Alien()
//{
//    int pos = rand()%380; //choose a random x position for alien
//    QRect area = QRect(pos,150,15,15);     //For testing purposes, the alien's top-left corner will start
//                                           //at (150,150) and its size will be 15 x 15.
//    alienArea = area;
//}



Alien::Alien(int id, int type, int x1, int y1)
{
    alienID = id;
    alienType = type;
    position = QPoint(x1,y1);
}

void Alien::draw(QPainter* painter)
{

    QPoint leftCorner = QPoint(position.x()-10,position.y()-10);
    alienRect = QRect(leftCorner,sizeOfAlien);
    if(alienType==1)
        painter->drawImage(alienRect,*alienImage1);//loads the tank image in the rectangle
    else    if(alienType==2)
        painter->drawImage(alienRect,*alienImage2);//loads the tank image in the rectangle
    else
        painter->drawImage(alienRect,*alienImage3);//loads the tank image in the rectangle
//painter->drawPixmap();
}

QRect Alien::getAlienRect()
{
    return alienRect;
}

int Alien::getAlienID()
{
    return alienID;
}

//int Alien::checkScreenEdge()
//{
//    if((alienArea.right())+1 >= 390)
//        return 1;                            //When alien object's right edge reaches x=390 or left edge reaches
//    else if ((alienArea.left() <= 10))       //x=10, the corresponding integer message will be sent out.
//        return 2;                            //0 = no edge     1 = hit right edge     2 = hit left egde
//    else
//        return 0;
//}

void Alien::setPos(int x1, int y1)
{
    position = QPoint(x1,y1);
    //    alienArea = QRect(topLeftX, topLeftY, 15, 15);
}

void Alien::setPos(const QPoint &ref)
{
    position+=ref;
}

QPoint Alien::getPos()
{
    return position;
}

//static QSize Alien::getSize()
QSize Alien::getSize()
{
    return sizeOfAlien;
}

int Alien::getAlienType()
{
    return alienType;
}

void Alien::deleteImages()
{
    delete alienImage1;
    delete alienImage2;
    delete alienImage3;
}

//void Alien::changePosition()
//{
//    int foundEdge = checkScreenEdge();
//    if( foundEdge == 0)
//    {
//        if(alienDirectionIndicator == 1)
//            alienArea.translate(5,0);
//        else if(alienDirectionIndicator == 2)
//            alienArea.translate(-5,0);                 //Based on the integer message from the checkScreenEdge()
//    }                                                  //function, the 'alien' moves according to the current
//    else if (foundEdge  == 1)                   //direction indicated by the alienDirectionIndicator attribute.
//    {                                                  //1 = moving right     2 = moving left
//        alienDirectionIndicator = 2;                   //When the 'alien' hits the edge of the screen, it changes the
//        alienArea.translate(0,15);                     //direction indicator attribute, moves the 'alien' down one line,
//        alienArea.translate(-5,0);                     //and moves the alien one increment in the new direction to move
//    }                                                  //it away from the screen edge and ensure that it continues in
//    else                                    //the new direction.
//    {
//        alienDirectionIndicator = 1;
//        alienArea.translate(0,15);
//        alienArea.translate(5,0);
//    }
//}
