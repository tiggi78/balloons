#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QString>
#include <QPixmap>
#include <QVector>

class imageLoader
{
public:
    imageLoader(const QString image, const quint16 rows, const quint16 cols, const quint16 frameWidth, const quint16 frameHeight);

    imageLoader(const QVector<QString>& normalFiles, const QVector<QString>& poppedFiles);

    const QPixmap& getNormalFrame(quint16 frame) const;
    const QPixmap& getPoppedFrame(quint16 frame) const;
    quint16 getMaxFrames() const;

private:
    QVector<QPixmap> pNormalFrames;
    QVector<QPixmap> pPoppedFrames;
    QPixmap pEmptyPixmap;
    quint16 pMaxFrames;
};

#endif // IMAGELOADER_H
