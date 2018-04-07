#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include <QMainWindow>
#include <QGraphicsView>
#include "graphicsscenecontroller.h"
#include "errorclass.h"
#include "toolspanel.h"

class QPixmap;

class FullScreen : public QMainWindow
{
    Q_OBJECT

public:
    FullScreen(QWidget *parent = 0);
    ~FullScreen();

private:
    //void grab_desktop();
    ToolsPanel              *tools;
    QGraphicsView           *viewer;
    GraphicsSceneController *controller;

public slots:
    void slot_Error(const ErrorClass &error );

    void start();
    void stop();

};

#endif // FULLSCREEN_H
