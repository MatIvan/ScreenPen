#include "fullscreen.h"


#include <QVBoxLayout>
#include <QDebug>
#include <QDialog>

FullScreen::FullScreen(QWidget *parent)
    : QMainWindow(parent)
{

    controller = new GraphicsSceneController( this );
    connect ( controller, SIGNAL( SignalError(ErrorClass)),
              this,       SLOT  ( slot_Error (ErrorClass)) );

    viewer = new QGraphicsView( this );
    viewer->setScene( controller );
    setCentralWidget( viewer );
    controller->setSceneRect(0,0, viewer->width() - 20, viewer->height() - 20);

    tools = new ToolsPanel( this, Qt::Tool );
    connect (tools, SIGNAL( closeToolPanel() ),
             this,  SLOT  ( close()          ) );

    start();
}

FullScreen::~FullScreen()
{

}

void FullScreen::start()
{
    stop();
    controller->grab_desktop();
    showFullScreen();
    tools->show();
}

void FullScreen::stop()
{
    tools->hide();
    hide();
    controller->clear();
}

void FullScreen::slot_Error(const ErrorClass &error)
{
    qDebug() << "Error: " << error.lastError();
}

