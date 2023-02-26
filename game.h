#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVector>

#include "balloonloader.h"
#include "soundmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Game; }
QT_END_NAMESPACE

class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void removePopped();
    void newBalloon();

private:
    Ui::Game *ui;
    QGraphicsScene* pScene;
    QVector<balloonLoader> pBalloons;
    QVector<QPixmap> pClouds;
    soundManager* pSoundMan;

    void setScene();
};
#endif // GAME_H
