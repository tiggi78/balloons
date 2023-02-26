#include "cloud.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

const qreal cloud::MAX_SPEED = 0.5;
const qreal cloud::SPEED_BOOST = 100.0;

cloud::cloud(QVector<QPixmap>& images, QGraphicsItem *parent): QGraphicsPixmapItem(parent), pImages(images)
{
    pSpeed = QRandomGenerator::global()->generateDouble()*MAX_SPEED*2-MAX_SPEED;
    setPixmap(pImages[QRandomGenerator::global()->bounded(pImages.size())]);
}

void cloud::advance(int phase)
{
    if ( 0 == phase )
    {
        // Check if cloud has reached scene boundaries
        if ((x() < scene()->sceneRect().left()) || (x() > scene()->sceneRect().right()))
        {
            pSpeed*=-1.0;
        }
    }
    if ( 1 == phase)
    {
        setX(x()+pSpeed);
    }
}

void cloud::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    pSpeed*=SPEED_BOOST;
    QTimer::singleShot(500,this,SLOT(resetSpeed()));
}
void cloud::resetSpeed()
{
    pSpeed/=SPEED_BOOST;
}
