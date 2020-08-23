#ifndef BUNKER_H
#define BUNKER_H

#include <QRect>
#include <QPainter>
#include <QVector>

class Bunker
{
public:
    Bunker(QPoint topLeft);
    bool bunkerIntersect(QRect shot);
    void draw(QPainter* painter);

private:
    QVector<QRect> bunkerBlock;
    QVector<int> blockStatus;

    static QSize blockSize;
    static QImage regBlock;
    static QImage oneHitBlock;
    static QImage twoHitBlock;
    static QImage threeHitBlock;
};

#endif // BUNKER_H
