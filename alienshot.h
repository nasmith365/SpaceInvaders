#ifndef ALIENSHOT_H
#define ALIENSHOT_H

#include <QPoint>
#include <QRect>
#include <QPainter>

class AlienShot
{
public:
    AlienShot(int shotType, QPoint pos); //specify initial position and type
    //three type of alienShots, send 1, 2 or 3
    void draw(QPainter* painter);
    QPoint getPosition();
    void setPosition(QPoint point);
    void moveDown();//move the shot one position down
    QRect getAlienshotRect();
    static void deleteImages();//delete static image objects, to be called in destructor of mainwindow
private:
    QSize size;//size of the alienshot
    int type;//type determines which imaage to be displayed
    QPoint position;//position of the alienshot
    QRect AlienshotRect; //rectangle bounding the alienshot

    //the static variables are used to draw the images of shots
    static QImage* alienshotImage1;
    static QImage* alienshotImage2;
    static QImage* alienshotImage3;

};

#endif // ALIENSHOT_H
