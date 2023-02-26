#include "balloon.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QEvent>
#include <QTouchEvent>

const qreal balloon::MAX_SPEED = 8.0;

balloon::balloon(balloonLoader& frames, QGraphicsItem* parent):
    QGraphicsPixmapItem(parent),pFrames(frames),
    frameNumber(0),pFrameAdvance(0),pPopped(false),
    pDeltax(0)
{
    pSpeed = QRandomGenerator::global()->generateDouble()*MAX_SPEED+.1 ;
    setPixmap(pFrames.getNormalFrame(0));
    setAcceptTouchEvents(true);
}

void balloon::update(const QRectF &rect)
{
    if( pPopped )
    {
        setPixmap(pFrames.getPoppedFrame(frameNumber));
    }
    else
    {
        setPixmap(pFrames.getNormalFrame(frameNumber));
    }
    QGraphicsPixmapItem::update(rect);
}
void balloon::advance(int phase)
{
    // Ballloon pops when reaches the top border of the scene
    if (y()< scene()->sceneRect().top())
    {
        hit();
    }
    quint16 frame = getFrameNumber();

    // Verify if this is the last frame for a popped balloon
    if (( 0 == phase) && pPopped)
    {
        if (pFrames.getMaxFrames() == (frame+1))
        {
            emit (popEndAnimation());
        }
    }
    if ( 1 == phase)
    {
        //Reduce frame rate for animation only
        pFrameAdvance++;
        pFrameAdvance%=4;
        if (0 == pFrameAdvance)
        {
            frame++;
            frame %= pFrames.getMaxFrames();
            /* Generate random x variations only when updating frame animation */
            pDeltax = QRandomGenerator::global()->generateDouble()*4.0-2.0;
            setFrameNumber(frame);

        }

        setY(y()-pSpeed);
        setX(x()+pDeltax);
        update();
    }
}

balloon::~balloon()
{
    //qDebug() <<"balloon::~balloon";
}

void balloon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    hit();
}

bool balloon::sceneEvent(QEvent* event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd: {
        QTouchEvent* touch = static_cast<QTouchEvent*>(event);
        qDebug()<<"touchEvent: "<<touch->pointCount();
    }
        return QGraphicsItem::sceneEvent(event);
        break;
    default:
        return QGraphicsItem::sceneEvent(event);
    }
}
void balloon::hit()
{
    if (!pPopped)
    {
        pPopped = true;
        setFrameNumber(0);
        emit(popped());
        update();
    }
}
quint16 balloon::getFrameNumber() const
{
    return frameNumber;
}

void balloon::setFrameNumber(quint16 newFrameNumber)
{
    if (frameNumber == newFrameNumber)
        return;
    frameNumber = newFrameNumber;
    pFrameAdvance = 0;
    emit frameNumberChanged();
}
