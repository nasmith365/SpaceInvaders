//Purpose: The entire program makes and runs the space invaders game. This particular class makes everything that is supposed to be
//	   on the screen and makes the game run by seeing if the shots hit something and then destroying it when it does.
//         Class is responsible for defining the position and drawing the image of mysteryship.
//Author: Nicholas Smith
//Date: 4/4/2013

#include <QPainter>
#include <QLine>
#include <cstdlib>
#include <math.h>
#include "mainwindow.h"
#include <iostream>
#include <ctime>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>

#undef DEBUG
#undef DEBUG1

MainWindow::MainWindow():QMainWindow()
{
#ifdef DEBUG1
    logfile.open("logfile.txt",std::ios::app);
#endif
    srand(time(0));//sets the seed for a random number

    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, Qt::black);//set the background black
    setPalette(pal);
    lives = 3;//the player starts with 3 lives
    level = 1;//the player always starts at level 1
    moveLeft = false;//have the aliens initially start moving right
    moveDown = false;//initially we do not want the rack to move down
    QWidget *region= new QWidget(this);
    score =0;//score starts initially at zero
    numShots=0;//the shot count starts initially at zero
//    gameOver=false;

    QString filename="highScore.txt";
    QFile file( filename );                   //At the beginning of each game, the high score and
    if ( file.open(QIODevice::ReadWrite) )    //player initials are retrieved from the highScore.txt file
    {                                         //and stored in variables to be used for the score display.
        QTextStream stream( &file );
        stream >> highScore;
        stream >> hsi;
    }

    tank = new Tank();//creates a new tank
    tankshot=NULL;//sets the tankshot object to NULL because there should not be one on the screen yet
    mysteryShip=NULL;//sets the mysteryship object to NULL because there should not be one on the screen yet
    //creates three bunkers(our screen can only allow for three bunkers)
    QPoint topLeft(112,450);
    bunker1 = new Bunker(topLeft);
    topLeft.setX(284);
    bunker2 = new Bunker(topLeft);
    topLeft.setX(456);
    bunker3 = new Bunker(topLeft);
    topLeft.setX(628);
    bunker4 = new Bunker(topLeft);

    //creates all the needed timers and set their intervals
    shotTimer = new QTimer();
    shotTimer->setInterval(20);
    alienTimer = new QTimer();
    alienTimer->setInterval(40);     //added a separate alien timer with a slower interval

    alienShotTimer = new QTimer();
    alienShotTimer->setInterval(1000);//aliens shoot every 100 msec

    alienShotSpeed= new QTimer();
    alienShotSpeed->setInterval(50);     //added a separate alien timer with a slower interval

    mysteryShipTimer = new QTimer();
    mysteryShipTimer->setInterval(20000);//added a timer to tell when the mysteryship appears (every 20 secs)

    mysteryShipMoveTimer = new QTimer();//mysteryship timer to calculate movement
    mysteryShipMoveTimer->setInterval(200);//moves the mysteryship every 250 msec.
    //sets the size of the mainwindow and makes it a set size so it can be resized
    this->setCentralWidget(region);
    this->resize(800,600);
    this->setMaximumSize(800,600);
    this->setMinimumSize(800,600);
    //connects the correct function to the correct timer so when it times out it runs the correct function
    drawAliens();//draws all the aliens
    shotSound = new QSound("../space-invaders/sounds/shoot.wav");
    killedSound = new QSound("../space-invaders/sounds/invaderkilled.wav");
    QObject::connect(shotTimer,SIGNAL(timeout()),this,SLOT(shotMoving()));
    QObject::connect(alienTimer,SIGNAL(timeout()),this,SLOT(moveAliens()));
    QObject::connect(mysteryShipTimer,SIGNAL(timeout()),this,SLOT(makeMysteryShip()));
    QObject::connect(mysteryShipMoveTimer,SIGNAL(timeout()),this,SLOT(moveMysteryShip()));
    QObject::connect(alienShotTimer,SIGNAL(timeout()),this,SLOT(createAlienShot()));
    QObject::connect(alienShotSpeed,SIGNAL(timeout()),this,SLOT(moveAlienShot()));

#ifdef DEBUG
    logfile << "MainWindow Constructor complete\n";
    logfile.flush();
#endif
}

void MainWindow::createAlienShot()
{//create a shot and put it in the vector so they can have 3 shot at a time
    int alienNum = alienShoot();
    AlienShot* temp = new AlienShot(alien.size()%3,alien[alienNum]->getPos());
    alienShots.push_back(temp);
}

void MainWindow::moveAlienShot()
{
    for (int i=0; i<alienShots.size(); ++i)
    {
        //alien shot hits a bunker, damages the bunker
        if((bunker1->bunkerIntersect(alienShots[i]->getAlienshotRect()))||(bunker2->bunkerIntersect(alienShots[i]->getAlienshotRect()))||(bunker3->bunkerIntersect(alienShots[i]->getAlienshotRect()))||(bunker4->bunkerIntersect(alienShots[i]->getAlienshotRect())))
        {
            //delete the alienShots
            AlienShot *temp = alienShots[i];
            alienShots.remove(i);
            delete temp;
        }
        else if(alienShots[i]->getAlienshotRect().intersects(tank->getTankRect()))//Alien shot hits a tank
        {
            //stop all the timers
            switchTimers(true);
            //makes the tank dissapear and makes the pointer point to null
            delete tank;
            tank=NULL;

            //delete the alienShot
            AlienShot *temp = alienShots[i];
            alienShots.remove(i);
            delete temp;

            if(tankshot!=NULL)//if there is a tank shot on the screen when the user dies it gets destroyed
            {
                delete tankshot;
                tankshot = NULL;
            }

            this->update();//gets rid of the bullet and tank because they are destroyed

            --lives;//lost a life so it subtracks
            if(lives == 0)
            {
//                gameOver=true;
                QMessageBox mbox;
                mbox.setText("Lost all the lives. Game over");
                mbox.exec();//game over

                if(score > highScore)
                {
                    QInputDialog highScoreInitials;
                    hsi = highScoreInitials.getText(this,"High score!","You got the high score! Enter your initials below:");

                    QString filename="highScore.txt";         //After the game ends, if the score for the current game is
                    QFile file( filename );                   //greater than the high score from the save file, the player
                    if (file.open(QIODevice::ReadWrite))      //is prompted to enter initials into a dialog box. Those initials,
                    {                                         //along with the new high score, are saved in a .txt file.
                        QTextStream stream(&file);
                        stream << score << " " << hsi;
                    }
                }
                return;
            }
            else
            {
                QMessageBox mbox;
                mbox.setText("Tank destroyed");
                mbox.exec();
                tank = new Tank();
                switchTimers(false);
            }
        }
        else if (alienShots[i]->getPosition().y()>this->height())//destroy the shot
        {
            //delete the alienShots
            AlienShot *temp = alienShots[i];
            alienShots.remove(i);
            delete temp;
        }
        else
        {//moves the alien Shot down if it didnt hit anything
            alienShots[i]->moveDown();
        }
    }//for loop
    this->update();
}//end of moveAlienShot()

int MainWindow::alienIntersection(QRect tankShot)//checks to see if the tank's shot intersects with a alien
{
    for(int i = 0; i<alien.size();++i)
    {
        if(tankShot.intersects(alien.value(i)->getAlienRect()))
        {
            return i;//returns the index of the alien the shot hit
        }
    }
    return -1;//nothing has been hit
}

int MainWindow::alienShoot()//picks which alien to shoot and returns the lowest one in the row
{

    int index = rand()%alien.size();//gets a pseudo random number inbetween 0 and the number of aliens left
    int selColumn = alien[index]->getAlienID()%11;//gets the column of the alien selected.
    for (int i= alien.size()-1; i>=0; i--)//goes through to try to find the lowest one in the column and then retunrs that index
        if(alien[i]->getAlienID()%11 == selColumn)
            return i;
    return alien.size()-1;//this is just in case the above does not return (which should not happen :)
}

void MainWindow::mysteryShipIntersection(QRect x)
{
    if(mysteryShip==NULL) return;//if there is no mysteryship then it is not possible for it to be hit
    if(x.intersects(mysteryShip->getMysteryShipRect()))//if it is a hit it the player increases score and the mysteryship gets destroyed
    {
        //mysteryship was destroyed so it plays the sound, stops the move timer for the ship and the timer for the shot
        //it also deletes the mystership and the tankshot and sets their values to null
        killedSound->play();
        mysteryShipMoveTimer->stop();
        shotTimer->stop();
        delete tankshot;
        delete mysteryShip;
        mysteryShip=NULL;
        mysteryShipTimer->start();
        //score for the mystership
        if(numShots%16 == 0)//every 16th shot is worth 300 points
            score += 300;//adds to the score when mystery ship is destroyed
        else if(numShots%10 == 0)//every 10th shot is worth 150
            score += 150;
        else if(numShots%5 == 0)//every 5th shot is worth 250 if it is not divisable by 10
            score += 250;
        else//all the other destroys are worth 200
            score +=200;
    }
}//end of mysteryShipIntersection


void MainWindow::drawAliens()
{
    int count =1;
    for(int j = 0; j<5;++j)//generates the 5 rows of aliens
    {
        if(j == 1)//changes the pick to the second kind of aliens
            count=2;
        if(j == 3)//changes the pick to the third kind of aliens
            count =3;
        for(int i =0; i<11; ++i)//generates the 11 aliens in each row
        {//pass id of the array as first argument
            Alien* temp = new Alien(j*11+i,count,200+40*i,100+40*j);//id,type,x pos, y pos
            alien.push_back(temp);//pushes back the alien into our alien vector
        }
    }
    switchTimers(false);//start the game
    //alien = new Alien(1,118,50);
}
//draws and redraws everything on the screen or creates new objects when this->update is called
void MainWindow::paintEvent(QPaintEvent *paintEvent)
{
#ifdef DEBUG
    logfile << "paintEvent() Start\n";
    logfile.flush();
#endif
    pen = new QPen();
    pen->setColor(Qt::white);
    pen->setWidth(2);
    QPainter painter(this);
    painter.setPen(*pen);

//    painter.drawLine(0,this->height()-75,this->width(),this->height()-75);//debugging line used for telling me that they are to low and player loses
    //draws or redraws all the alien shots on the screen if there is any

    for(int i=0; i<alienShots.size(); ++i)
    {
        alienShots[i]->draw(&painter);
    }
    //if there is a mysteryship object it will drawn or redrawn
    if(mysteryShip != NULL)
    {
        mysteryShip->draw(&painter);
    }
    //if there is a tankshot object it will be drawn or redrawn
    if(tankshot != NULL)
    {
        tankshot->draw(&painter);
    }
    //draws or redraws all the aliens on the screen
    for(int i = 0; i<alien.size();++i)
    {
        if(alien.value(i) !=NULL)
        {
            alien.value(i)->draw(&painter);
        }
    }
    //if there is a tank object it will be drawn or redrawn
    if (tank!=NULL)
    {
        tank->draw(&painter);
    }
    //draws or redraws all four bunkers
    bunker1->draw(&painter);
    bunker2->draw(&painter);
    bunker3->draw(&painter);
    bunker4->draw(&painter);

    QString str = "Score: " + QString::number(score) + ", Level: " +QString::number(level) + ", Lives: " + QString::number(lives) + ", High Score: " + QString::number(highScore) + "  " + hsi;
    //is the screen object of all of the game stats, took number of shots off so the player has to work harder to get max points from mystery ship
    painter.drawText(0,20,str);//put all the text in the top left corner

//    QString over = "GAME OVER";
//    if (gameOver)                       //when the game is over, display "GAME OVER" in the center of the screen
//        painter.drawText(375,275,over);

#ifdef DEBUG
    logfile << "paintEvent() complete\n";
    logfile.flush();
#endif
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    int key = ke->key();
    if(lives != 0)
    {
        if(key==Qt::Key_P)//pause the game if the P key is pressed
        {
            switchTimers(alienTimer->isActive());//switch all the timers to be either on or off
        }
    }
    if(!alienTimer->isActive()) return; //game is paused
    if(key==32)//shoot a tankshot if there isn't one currently on the screen when the space bar is pressed
    {//if there is not a tankshot object currently on the screen it calls the shoot function
        if(tankshot == NULL)
            shoot();
    }
    else if(key==Qt::Key_Left)//move the tank left when the left arrow is pressed if there is a tank object
    {
        if(tank!=NULL)
            tank->moveLeft();
        this->update();
    }
    else if(key==Qt::Key_Right)//move the tank right when the right arrow is pressed if there is a tank object
    {   if(tank!=NULL)
            tank->moveRight(this->width());
        this->update();
    }
 }

void MainWindow::shoot()
{//generates a tankshot object that starts at the tanks position
    shotSound->play();
    tankshot = new TankShot(tank->getPosition());//create the tankshot object, start the shot where tank is
    numShots++;//increases the number of shots becuase it is used for mysteryship
    shotTimer->start();
}
//if there isn't a tankshot object on the screen it exits the function
//if there is a tankshot object on the screen it see if it hit anything and if it does then it disappears if it goes off the screen it still gets destroyed
void MainWindow::shotMoving()
{
    if(tankshot==NULL) return;
    int destroyedAlien = alienIntersection(tankshot->getTankshotRect());//checks to see if the shot intersects with an alien
    mysteryShipIntersection(tankshot->getTankshotRect());//checks to see if the shot hits the mysteryship
    //see if the shot hits the bunker and if it does it will damage the bunker
    if((bunker1->bunkerIntersect(tankshot->getTankshotRect()))|| (bunker2->bunkerIntersect(tankshot->getTankshotRect())) ||(bunker3->bunkerIntersect(tankshot->getTankshotRect()))||(bunker4->bunkerIntersect(tankshot->getTankshotRect())))
    {//stops the shot timer and deletes the tank shot because it hit the bunker
        delete tankshot;
        shotTimer->stop();
    }
    if (tankshot->getPos().y()<=5)//left the top of the screen
    {
        delete tankshot; //delete tankshot object if it did not hit a target
        tankshot=NULL;
        shotTimer->stop();
    }
    else
        if(destroyedAlien != -1)//hit an alien
        {
            shotTimer->stop();
            killedSound->play();
            //checks if the destroyed alien is in the top row, if so it adds 30 to score
            if(alien.at(destroyedAlien)->getAlienType() == 1)
                score+=30;
            //checks if the destroyed alien is in the middle row, if so it adds 20 points to score
            else if(alien.at(destroyedAlien)->getAlienType()== 2)
                score +=20;
            //if it is not in the top or middle rows then it must be in the bottom row so it adds 10 points to score
            else
                score +=10;
            delete tankshot;
            tankshot=NULL;
            Alien *temp = alien[destroyedAlien];//get handle to Alien object
            alien.remove(destroyedAlien);//remove pointer from the vector
            delete temp;//delete the alien object
        }
        else
        {//moves the tankshot because it hasnt hit anything
            tankshot->moveUp();
            shotTimer->start();
        }
    this->update();
}

void MainWindow::checkAlienScreenEdge()//is going to check if the aliens need to move down because they are at the edge and is going to check to see if they are low enough where the player will lose once they hit the wall
{   int flag=0;
    //goes through all the aliens to see if there are any hitting the wall and then once it finds one it breaks out of the loop.
    for(int i = 0; i<alien.size();++i)
    {
        QSize alienSize = alien.value(i)->getSize();//gets the size of the alien
        if(alien.value(i)->getPos().y()>=this->height()-75)//hit the bottom so the game should end
        {
            switchTimers(true);//stops everything because the player lost the game
            lives = 0;
//            gameOver=true;
            QMessageBox mbox;
            mbox.setText("You got Captured. Game Over");
            mbox.exec();
            flag = 3;

            if(score > highScore)
            {
                QInputDialog highScoreInitials;
                hsi = highScoreInitials.getText(this,"High score!","You got the high score! Enter your initials below:");

                QString filename="highScore.txt";          //After the game ends, if the score for the current game is
                QFile file( filename );                    //greater than the high score from the save file, the player
                if (file.open(QIODevice::ReadWrite))       //is prompted to enter initials into a dialog box. Those initials,
                {                                          //along with the new high score, are saved in a .txt file.
                    QTextStream stream(&file);
                    stream << score << " " << hsi;
                }
            }
            return;
        }
        if(moveDown == false)//if it hasn't just moved down it will check the screen edge
        {
            if(alien.value(i)->getPos().x()+(alienSize.width())>= this->width())//checks to see if the aliens are at the right wall
            {
                flag=1;
                break;
            }
            else if(alien.value(i)->getPos().x()-(alienSize.width()) <= 0)//checks to see if the aliens are at the left wall
            {
                flag=2;
                break;
            }
        }
    }
    if(moveDown == true)
    {
        moveDown = false;
    }

    if (flag==1)//they hit the right wall, move down and reverse direction
    {
        moveLeft = true;//move left
        moveDown = true;//move down next time
        moveAliensLeft();
    }
    if (flag==2)//hit the left wall, move down and reverse direction
    {
        moveLeft = false;//move right
        moveDown = true;//move down next time
        moveAliensRight();
    }
}

void MainWindow::switchTimers(bool stop)
{
    if(stop)//if we are sent true then we want all the timers to stop or else we want them to start
    {
        alienTimer->stop();
        mysteryShipTimer->stop();
        alienShotTimer->stop();
        alienShotSpeed->stop();
        shotTimer->stop();
        mysteryShipMoveTimer->stop();
    }
    else
    {
        mysteryShipTimer->start();
        alienShotTimer->start();
        alienShotSpeed->start();
        shotTimer->start();
        alienTimer->start();
        mysteryShipMoveTimer->start();
    }
}


void MainWindow::moveAliens()
{
    if(alien.size() == 0)//checks to see if all the aliens are destroyed and if they are level increase and you start again
    {
        ++level;
        if(lives < 3)//max number of lives is 3 so if you have less then three you gain one once level increase
            ++lives;
        if(level >= 7)//seven is the hardest level and anything after that the shots do not get faster
        {
            alienShotTimer->setInterval(1000-level*100);//sets the alienshot timer to be base on level each time level increase
            alienShotTimer->start();
        }
        moveLeft = false;//have the aliens start moving right
        moveDown = false;//do not want the rack to move down
        drawAliens();
    }
    alienTimer->setInterval(sqrt((alien.size()/55.0))*400);//changes the speed of the alien movement depending on how many are left
    alienTimer->start();//starts the timer with the new interval
    checkAlienScreenEdge();//sees if the aliens are at the edge of the screen
    //moves the aliens in the correct direction
        if (moveLeft)
            moveAliensLeft();
        else
            moveAliensRight();
        this->update();
}

void MainWindow::makeMysteryShip()
{
#ifdef DEBUG1
    logfile << "Width of screen" << this->width();
    logfile.flush();
#endif

    if (mysteryShip!=NULL) return;//just in case if mystery ship already exists.
    if(numShots%2==0)//the shot count is an even number
    {
        mysteryShip = new MysteryShip(2,10,60);//the mysteryship should move right
    }
    else//shot count is a odd number
    {
        mysteryShip = new MysteryShip(1,this->width()-10,60);//the mysteryship should move left
    }
    mysteryShipMoveTimer->start();
}

//Update the mystery ship position
void MainWindow::moveMysteryShip()
{
    //delete the ship if it reached the other end and stop the timer
    if(mysteryShip==NULL) return;
    if (mysteryShip->checkIfReachedOtherEnd(this->width()))
    {
        delete mysteryShip;
        mysteryShip=NULL;
        mysteryShipMoveTimer->stop();
    }
    else
        mysteryShip->move();//update the position
}

void MainWindow::moveAliensRight()
{
    alien.size();
    //if movedown is true it will only move down and not to the right
    QPoint point(moveDown?0:10,moveDown?10:0);
    for(int i = 0; i<alien.size();++i)
    {//moves all the aliens by setting position to the point
        alien.value(i)->setPos(point);
    }
}

void MainWindow::moveAliensLeft()
{
    //if movedown is true it will only move down and not move to the left
    QPoint point(moveDown?0:-10,moveDown?10:0);
    for(int i = 0; i<alien.size();++i)
    {//moves all the aliens by setting position to the point
        alien.value(i)->setPos(point);
    }
}

MainWindow::~MainWindow()
{//destroys everything that was created
    delete shotSound;
    delete killedSound;
    delete alienTimer;
    delete shotTimer;
    Alien::deleteImages();
    AlienShot::deleteImages();
    if(tank!=NULL)
    {
        delete tank;
        tank= NULL;
    }
    if(tankshot!=NULL)
    {
        delete tankshot;
        tankshot= NULL;
    }
    for(int i = 0; i<alien.size();++i)//deletes the aliens left on the screen
    {
        Alien *temp = alien[i];
        alien.remove(i);
        delete temp;
    }
    for(int i = 0; i<alienShots.size(); ++i)//deletes the alien shots left on the screen
    {
        AlienShot *temp = alienShots[i];
        alienShots.remove(i);
        delete temp;
    }
}
