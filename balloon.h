#ifndef BALLOON_H
#define BALLOON_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include "imageloader.h"

class balloon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    static const quint16 MAX_SPEED = 10;
    balloon(imageLoader& frames, quint16 speed = 1 ,QGraphicsItem* parent=NULL);
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
    imageLoader& pFrames;
    quint16 frameNumber;
    quint16 pFrameAdvance;
    bool pPopped;
    quint16 pSpeed;
    qint16 pDeltax;
    void hit();
    Q_PROPERTY(quint16 frameNumber READ getFrameNumber WRITE setFrameNumber NOTIFY frameNumberChanged)

};

#endif // BALLOON_H
