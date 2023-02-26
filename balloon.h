#ifndef BALLOON_H
#define BALLOON_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include "balloonloader.h"

class balloon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    balloon(balloonLoader& frames ,QGraphicsItem* parent=NULL);
    quint16 getFrameNumber() const;
    void setFrameNumber(quint16 newPFrameNumber);
    void update(const QRectF &rect = QRectF());
    void advance(int phase) override;
    ~balloon();
signals:
    void frameNumberChanged();
    void popEndAnimation();
    void popped();

protected:
    bool sceneEvent(QEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const qreal MAX_SPEED;
    balloonLoader& pFrames;
    quint16 frameNumber;
    quint16 pFrameAdvance;
    bool pPopped;
    qreal pSpeed;
    qreal pDeltax;

    void hit();
    Q_PROPERTY(quint16 frameNumber READ getFrameNumber WRITE setFrameNumber NOTIFY frameNumberChanged)

};

#endif // BALLOON_H
