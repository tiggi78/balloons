#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QSoundEffect>
#include <QUrl>
#include <QMediaPlayer>
#include <QVector>

class soundManager : public QObject
{
    Q_OBJECT

public:
    soundManager(QObject* parent=NULL);
    ~soundManager();
    void initialize();
private:
    QVector<QSoundEffect*> pSounds;
    QVector<QUrl> pMusic;
    quint32 pCurrentTrack;
    QMediaPlayer* pMusicPlayer;
public slots:
    void playPopEffect();
    void nextMusic(QMediaPlayer::PlaybackState newState);
};

#endif // SOUNDMANAGER_H
