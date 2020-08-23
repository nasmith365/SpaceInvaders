//Purpose: Define Mysteryship class which represents the ufo/saucer that appears on the top.
//         Class is responsible for defining the position and drawing the image of mysteryship.
//Author: Nicholas Smith
//Date: 4/4/2013

#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H
#include <QPoint>
#include <QPainter>

class MysteryShip
{
private:
    int direction;//1 = ship is going left, 2 = ship is going right
    QPoint position;
    QRect mysteryShipRect;
    QImage *mysteryShipImage;
    QSize size;
public:
    MysteryShip(int direction, int x1, int y1);
    //Mystery Ship goes to left (direction=1) or right (direction=2)
    //If ship is going left, (x1,y1) should be top right corner.

    ~MysteryShip();
    void setPosition(int x1, int y1);
    QPoint getPosition();
    void draw(QPainter* painter);//draw the ship's image
    QRect getMysteryShipRect();//returns the QRect bounding the ship
    int getDirection();

    //this function is to check if the ship has reached the other end of screen
    //in that case, mainwindow should destroy the object.
    bool checkIfReachedOtherEnd(int screenWidth);

public slots:
    void move();//move the mysteryship in horizontal direction

};

#endif // MYSTERYSHIP_H
