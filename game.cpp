#include "game.h"
#include "ui_game.h"
#include <QTimer>
#include <QRandomGenerator>
#include "balloon.h"
#include "cloud.h"

const qreal X_MAX = 640.0;
const qreal Y_MAX = 320.0;

Game::Game(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);
    pSoundMan=new soundManager(this);
    pSoundMan->initialize();
    setScene();


    QTimer* animator = new QTimer(this);
    connect(animator,SIGNAL(timeout()),pScene,SLOT(advance()));
    animator->start(40);

    QTimer* generator = new QTimer(this);
    connect(generator,SIGNAL(timeout()),this,SLOT(newBalloon()));
    generator->start(1000);

}

void Game::newBalloon()
{
    quint32 index = QRandomGenerator::global()->bounded(pBalloons.size());
    balloon* b = new balloon(pBalloons[index]);
    connect(b,SIGNAL(popEndAnimation()),this,SLOT(removePopped()));

    connect(b,SIGNAL(popped()),pSoundMan,SLOT(playPopEffect()));

    qreal x = QRandomGenerator::global()->generateDouble()*2*X_MAX-X_MAX;
    qreal y = Y_MAX;
    b->setPos(x,y);
    b->setTransformationMode(Qt::SmoothTransformation);
    b->setScale(.3);
    //qDebug()<<"Game::newBalloon at "<<b->pos();

    pScene->addItem(b);

    //qDebug()<<"Game::SceneRect:"<<pScene->sceneRect();
    //qDebug()<<"Game::viewRect:"<<ui->mainView->rect();


}

void Game::setScene(){

    /*
    pBalloons.append(imageLoader(":/images/balloon_blue.png",2,3,16,32));
    pBalloons.append(imageLoader(":/images/balloon_red.png",2,3,16,32));
    pBalloons.append(imageLoader(":/images/balloon_green.png",2,3,16,32));
    pBalloons.append(imageLoader(":/images/balloon_purple.png",2,3,16,32));
    pBalloons.append(imageLoader(":/images/balloon_yellow.png",2,3,16,32));
    */
    QVector<QString> normal = {":/images/blue-balloon/1.png"};
    QVector<QString> popped = {":/images/blue-balloon/2.png",":/images/blue-balloon/3.png",
                               ":/images/blue-balloon/4.png",":/images/blue-balloon/5.png",
                               ":/images/blue-balloon/6.png"};

    pBalloons.append(balloonLoader(normal,popped));
    normal = {":/images/yellow-balloon/1.png"};
    popped = {":/images/yellow-balloon/2.png",":/images/yellow-balloon/3.png",
              ":/images/yellow-balloon/4.png",":/images/yellow-balloon/5.png",\
              ":/images/yellow-balloon/6.png"};
    pBalloons.append(balloonLoader(normal,popped));

    normal = {":/images/green-balloon/1.png"};
    popped = {":/images/green-balloon/2.png",":/images/green-balloon/3.png",
              ":/images/green-balloon/4.png",":/images/green-balloon/5.png",\
              ":/images/green-balloon/6.png"};
    pBalloons.append(balloonLoader(normal,popped));

    normal = {":/images/orange-balloon/1.png"};
    popped = {":/images/orange-balloon/2.png",":/images/orange-balloon/3.png",
              ":/images/orange-balloon/4.png",":/images/orange-balloon/5.png",\
              ":/images/orange-balloon/6.png"};
    pBalloons.append(balloonLoader(normal,popped));

    normal = {":/images/pink-balloon/1.png"};
    popped = {":/images/pink-balloon/2.png",":/images/pink-balloon/3.png",
              ":/images/pink-balloon/4.png",":/images/pink-balloon/5.png",\
              ":/images/pink-balloon/6.png"};

    pBalloons.append(balloonLoader(normal,popped));
    normal = {":/images/purple-balloon/1.png"};
    popped = {":/images/purple-balloon/2.png",":/images/purple-balloon/3.png",
              ":/images/purple-balloon/4.png",":/images/purple-balloon/5.png",\
              ":/images/purple-balloon/6.png"};

    pBalloons.append(balloonLoader(normal,popped));
    normal = {":/images/red-balloon/1.png"};
    popped = {":/images/red-balloon/2.png",":/images/red-balloon/3.png",
              ":/images/red-balloon/4.png",":/images/red-balloon/5.png",\
              ":/images/red-balloon/6.png"};
    pBalloons.append(balloonLoader(normal,popped));


    pScene = new QGraphicsScene(this);
    pScene->addLine(0,0,X_MAX,0,QPen(Qt::red));
    pScene->addLine(0,0,0,Y_MAX,QPen(Qt::yellow));
    pScene->addRect(-X_MAX,-Y_MAX,2*X_MAX,2*Y_MAX);

    pScene->setBackgroundBrush(Qt::blue);
    pClouds.append(QPixmap(":/images/Cloud_1.png"));
    pClouds.append(QPixmap(":/images/Cloud_2.png"));
    pClouds.append(QPixmap(":/images/Cloud_3.png"));
    for (quint16 i=0; i< 20; ++i)
    {
        qreal x = QRandomGenerator::global()->generateDouble()*2*X_MAX-X_MAX;
        qreal y = QRandomGenerator::global()->generateDouble()*2*Y_MAX-Y_MAX;
        cloud* cl = new cloud(pClouds);
        cl->setPos(x,y);
        cl->setTransformationMode(Qt::SmoothTransformation);
        cl->setScale(.3);
        pScene->addItem(cl);

    }
    ui->mainView->setScene(pScene);
    pScene->setSceneRect(-X_MAX,-Y_MAX,2*X_MAX,2*Y_MAX);
    ui->mainView->setSceneRect(QRect());
}
Game::~Game()
{
    delete ui;
}

void Game::removePopped()
{
 //   qDebug()<<"Game::removePopped()"<<QObject::sender();
    pScene->removeItem(qobject_cast<balloon*>(QObject::sender()));
    delete QObject::sender();
}
