#include "balloonloader.h"

balloonLoader::balloonLoader(const QString image,const quint16 rows, const quint16 cols, const quint16 frameWidth, const quint16 frameHeight)
{
    QPixmap fullImage(image);
    /*
     * First row contains normal image animation
     * Second row contains popped image animation
     */
    QVector<QPixmap>* frameContainter[2]={ &pNormalFrames, &pPoppedFrames };
    for (quint16 r=0; r<rows;++r)
    {
        for (quint16 c=0; c<cols;++c)
        {
            frameContainter[r]->append(fullImage.copy(c*frameWidth,r*frameHeight,frameWidth,frameHeight));
        }
    }
    pMaxFrames = cols;
}

balloonLoader::balloonLoader(const QVector<QString>& normalFiles, const QVector<QString>& poppedFiles){
    pMaxFrames = qMax(normalFiles.size(), poppedFiles.size());
    pNormalFrames.resize(pMaxFrames);
    pPoppedFrames.resize(pMaxFrames);
    if(1 == normalFiles.size())
    {
        for( int i=0; i< pMaxFrames; ++i)
            pNormalFrames[i].load(normalFiles[0]);
    }
    else
    {
        for( int i=0; i< pMaxFrames; ++i)
            pNormalFrames[i].load(normalFiles[i%normalFiles.size()]);

    }
    if(1 == poppedFiles.size())
    {
        for( int i=0; i< pMaxFrames; ++i)
            pPoppedFrames[i].load(poppedFiles[0]);
    }
    else
    {
        for( int i=0; i< pMaxFrames; ++i)
            pPoppedFrames[i].load(poppedFiles[i%poppedFiles.size()]);

    }
}

const QPixmap& balloonLoader::getNormalFrame(quint16 frame) const
{
    if( pMaxFrames > frame){
        return pNormalFrames[frame];
    }
    else{
        return pEmptyPixmap;
    }
}
const QPixmap& balloonLoader::getPoppedFrame(quint16 frame) const
{
    if( pMaxFrames > frame){
        return pPoppedFrames[frame];
    }
    else{
        return pEmptyPixmap;
    }
}
quint16 balloonLoader::getMaxFrames() const{
    return pMaxFrames;
}
