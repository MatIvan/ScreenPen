#include "fullscreen.h"

#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
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

    this->showFullScreen();
    tools->show();
}

FullScreen::~FullScreen()
{

}

void FullScreen::slot_Error(const ErrorClass &error)
{
    qDebug() << "Error: " << error.lastError();
}

//void FullScreen::grab_desktop()
//{
//    hide();
//    QScreen *screen = QApplication::primaryScreen();
//    desktop_pixmap = screen->grabWindow(QApplication::desktop()->winId());
//    show();
//}
