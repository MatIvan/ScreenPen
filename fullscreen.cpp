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

    connect (tools,      SIGNAL( changedTool( int ) ),
             controller, SLOT  ( setTool( int )     ) );

    connect (tools, SIGNAL( changedTool( int )  ),
             this,  SLOT  ( changeCursor( int ) ) );

    start();
    changeCursor( ToolsID::tool_pen );
}

FullScreen::~FullScreen()
{

}

QCursor FullScreen::makeCursor(const QString &file, int hot_x, int hot_y )
{
    QPixmap pix( file );
    return QCursor( pix.scaledToHeight( 16 ), hot_x, hot_y );
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

void FullScreen::changeCursor(int tool_id)
{
    switch(tool_id){
    case ToolsID::tool_non :    viewer->unsetCursor();
                                break;
    case ToolsID::tool_brash :  viewer->setCursor( makeCursor( ":/icons/square", -1, -1 ) );
                                break;
    case ToolsID::tool_eraser : viewer->setCursor( makeCursor( ":/icons/eraser",  0, 15 ) );
                                break;
    case ToolsID::tool_pen :    viewer->setCursor( makeCursor( ":/icons/pen"   ,  0, 15 ) );
                                break;
    case ToolsID::tool_circle :
    case ToolsID::tool_line :
    case ToolsID::tool_rect :   viewer->setCursor( Qt::CrossCursor );
                                break;
    default : viewer->unsetCursor();
    }
}

void FullScreen::slot_Error(const ErrorClass &error)
{
    qDebug() << "Error: " << error.lastError();
}

