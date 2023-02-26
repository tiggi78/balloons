#ifndef CLOUD_H
#define CLOUD_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QVector>
#include <QPixmap>

class cloud : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    cloud(QVector<QPixmap>& images, QGraphicsItem *parent=NULL);
    //void update(const QRectF &rect = QRectF());
    void advance(int phase) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const qreal MAX_SPEED;
    static const qreal SPEED_BOOST;
    qreal pSpeed;
    QVector<QPixmap>& pImages;
private slots:
    void resetSpeed();
};

#endif // CLOUD_H
