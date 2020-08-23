#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPen>
#include <QLabel>
#include <QSound>
#include <QTimer>
#include <QPoint>

#include "tankshot.h"
#include "tank.h"
#include "alien.h"
#include "mysteryship.h"
#include "alienshot.h"
#include "bunker.h"

#include <fstream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    ~MainWindow();

private:
    std::ofstream logfile;
    int alienIntersection(QRect tankShot);
    int alienShoot();
    void mysteryShipIntersection(QRect x);//might go to mysteryship.cpp
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *ke);
    void moveAliensRight();
    void moveAliensLeft();
    void drawAliens();
    void shoot();
    void checkAlienScreenEdge();
    void switchTimers(bool stop);

private slots:
    void shotMoving();
    void moveAliens();
    void makeMysteryShip();
    void moveMysteryShip();
    void createAlienShot();
    void moveAlienShot();
    protected:
        QTimer *shotTimer, *alienTimer, *mysteryShipTimer, *mysteryShipMoveTimer, *alienShotTimer;
        QTimer *alienShotSpeed;
        QVector<Alien*> alien;
        QVector <AlienShot*> alienShots;
        Tank* tank;
        TankShot* tankshot;
        MysteryShip* mysteryShip;
        Bunker *bunker1, *bunker2, *bunker3, *bunker4;
        QPen *pen;
        QSound* killedSound;
        QSound* shotSound;  //so that the sound needs to be loaded in memory only once
        QString hsi;  //variable used to store initials of user that obtained a high score
        int score, highScore;//keep score of how many aliens were shot
        int numShots;//keep track of how many shots were fired
        int lives;//keeps track of the number of lives the player has
        int level;//will keep track of the current level the player is at
        bool moveDown;//Is going to keep track to see if the rack need to move down or not
        bool moveLeft;//Keeps track of which direction the rack needs to move
//        bool gameOver;//a variable to keep track to see if the game is over
 };

#endif // MAINWINDOW_H
