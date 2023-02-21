#include "soundmanager.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QAudioOutput>

#include <QTimer>

soundManager::soundManager(QObject* parent) : QObject(parent)
{
}
soundManager::~soundManager()
{
}

void soundManager::initialize()
{
/*
    QMediaPlayer* effect = new QMediaPlayer(this);
    effect->setSource(QUrl("qrc:/sounds/pop.wav"));
    effect->setAudioOutput(audioOutput);
    pSounds.append(effect);

    audioOutput = new QAudioOutput(this);
    effect = new QMediaPlayer(this);
    effect->setSource(QUrl("qrc:/sounds/cork.wav"));
    effect->setAudioOutput(audioOutput);
    pSounds.append(effect);
*/
    QSoundEffect* effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(":/sounds/pop.wav"));
    pSounds.append(effect);

    effect = new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(":/sounds/cork.wav"));
    pSounds.append(effect);

    effect = new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(":/sounds/balloonPop.wav"));
    pSounds.append(effect);

    pMusic.append(QUrl("qrc:/music/Chiptune.mp3"));
    pMusic.append(QUrl("qrc:/music/fantasy.mp3"));
    pMusic.append(QUrl("qrc:/music/music.mp3"));

    pMusicPlayer = new QMediaPlayer(this);
    connect (pMusicPlayer,SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
             this, SLOT(nextMusic(QMediaPlayer::PlaybackState)));
    /* Starts playback of first music file */
    pCurrentTrack = pSounds.size()-1;
    nextMusic(QMediaPlayer::StoppedState);
}

void soundManager::playPopEffect()
{
    quint16 index = QRandomGenerator::global()->generate()%pSounds.size();
    QSoundEffect* effect = pSounds[index];

    qDebug()<<"playPopEffect:: index:"<<index<<"BEFORE isPlaying: " <<effect->isPlaying();
    if(effect->isPlaying())
    {
        effect->stop();
    }
    qDebug()<<"playPopEffect:: index:"<<index<<"AFTER isPlaying: " <<effect->isPlaying();

    effect->play();
}

void soundManager::nextMusic(QMediaPlayer::PlaybackState newState)
{
    qDebug()<<"nextMusic::newState:"<<newState;

    if (QMediaPlayer::StoppedState == newState)
    {
        pCurrentTrack++;
        pCurrentTrack%=pMusic.size();
        /* Sound is not working after one or two tracks.
         * putting everytime a new QAudioOutput seems to solve the issue ...
         */
        QAudioOutput* oldAudioOutput=pMusicPlayer->audioOutput();
        pMusicPlayer->setAudioOutput(new QAudioOutput(this));
        if (nullptr !=oldAudioOutput)
        {
            delete(oldAudioOutput);
        }
        pMusicPlayer->setSource(pMusic[pCurrentTrack]);

        pMusicPlayer->play();
        qDebug()<<"nextMusic:: play song:"<<pCurrentTrack;

    }
}
