//Purpose: The Bunker class controls the shape and status of a bunker and its blocks.
//Author: Nicholas Smith
//Date: 4/4/2013

#include "bunker.h"

QImage Bunker::regBlock("../space-invaders/images/bunkerPiece.jpg");
QImage Bunker::oneHitBlock("../space-invaders/images/bunkerPiece1Hit.jpg");
QImage Bunker::twoHitBlock("../space-invaders/images/bunkerPiece2Hits.jpg");
QImage Bunker::threeHitBlock("../space-invaders/images/bunkerPiece3Hits.jpg");
QSize Bunker::blockSize = QSize(15,15);

Bunker::Bunker(QPoint topLeft)
{
    QRect b0(topLeft,blockSize);
    topLeft.setY(topLeft.y()+15);
    QRect b1(topLeft,blockSize);
    topLeft.setY(topLeft.y()+15);
    QRect b2(topLeft,blockSize);
    topLeft.setY(topLeft.y()-30);
    topLeft.setX(topLeft.x()+15);
    QRect b3(topLeft,blockSize);      //the Bunker constructor places all of the QRects of the bunker in reference
    topLeft.setY(topLeft.y()+15);     //to the point given to it, which represents the top left corner of the bunker.
    QRect b4(topLeft,blockSize);
    topLeft.setY(topLeft.y()-15);
    topLeft.setX(topLeft.x()+15);
    QRect b5(topLeft,blockSize);
    topLeft.setY(topLeft.y()+15);
    QRect b6(topLeft,blockSize);
    topLeft.setY(topLeft.y()-15);
    topLeft.setX(topLeft.x()+15);
    QRect b7(topLeft,blockSize);
    topLeft.setY(topLeft.y()+15);
    QRect b8(topLeft,blockSize);
    topLeft.setY(topLeft.y()+15);
    QRect b9(topLeft,blockSize);

    bunkerBlock.push_back(b0);
    bunkerBlock.push_back(b1);
    bunkerBlock.push_back(b2);
    bunkerBlock.push_back(b3);     //All of the newly created QRects are stored in an array for easy referencing.
    bunkerBlock.push_back(b4);
    bunkerBlock.push_back(b5);
    bunkerBlock.push_back(b6);
    bunkerBlock.push_back(b7);
    bunkerBlock.push_back(b8);
    bunkerBlock.push_back(b9);

    for(int i = 0; i < 10; i++)     //An array of integers is used to keep track of the status of each block.
        blockStatus.push_back(4);   //4 = no hits    3 = one hit    2 = two hits    1 = three hits     0 = destroyed
}

bool Bunker::bunkerIntersect(QRect shot)
{
    for(int i = 0; i < bunkerBlock.size(); i++)
    {
        if(bunkerBlock[i].intersects(shot))
        {
            blockStatus[i]--;           //Each time a block is hit by a bullet, whether its from an alien or the tank,
            return true;                //the status integer for that block is decremented.
        }
    }
    return false;
}

void Bunker::draw(QPainter *painter)
{
    for(int i = 0; i < bunkerBlock.size(); i++)
    {
        if (blockStatus[i] == 4)
            painter->drawImage(bunkerBlock[i],regBlock);           //The bunker draw() method acts as a status checker.
        else if (blockStatus[i] == 3)                              //Based on the blockStatus of a particular block, the
            painter->drawImage(bunkerBlock[i],oneHitBlock);        //method places the appropriate image in the
        else if (blockStatus[i] == 2)                              //corresponding QRect.
            painter->drawImage(bunkerBlock[i],twoHitBlock);
        else if (blockStatus[i] == 1)
            painter->drawImage(bunkerBlock[i],threeHitBlock);
        else if (blockStatus[i] == 0)
        {
            bunkerBlock.remove(i);        //If a blockStatus reaches zero, the QRect and its corresponding status integer
            blockStatus.remove(i);        //are completely removed.
        }

    }
}
