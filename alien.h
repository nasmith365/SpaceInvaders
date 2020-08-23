#ifndef ALIEN_H
#define ALIEN_H

#include <QRect>
#include <QImage>

class Alien
{

private:
static QImage* alienImage1;
static QImage* alienImage2;
static QImage* alienImage3;
static QSize sizeOfAlien;

protected:
    int alienID;
    int alienType;
    QPoint position; //its easier to communicate with the board in terms of QPoint than with QRect
    QRect alienRect;  //can be generated from position if required

public:

//    Alien();
    Alien(int id, int type, int x1, int y1);
    void draw(QPainter* painter);
    void setPos(int topLeftX, int topLeftY);
    void setPos(const QPoint &ref);
    QPoint getPos();
    //static QSize getSize();
    QSize getSize();
    QRect getAlienRect();
    static void deleteImages();
    int getAlienID();
    int getAlienType();
};

#endif // ALIEN_H
