#include "fullscreen.h"


#include <QVBoxLayout>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>

FullScreen::FullScreen(QWidget *parent)
    : QMainWindow(parent)
{

    controller = new GraphicsSceneController( this );
    connect ( controller, SIGNAL( SignalError(ErrorClass)),
              this,       SLOT  ( slot_Error (ErrorClass)) );

    viewer = new QGraphicsView( this );
    viewer->setScene( controller );

    controller->setSceneRect(0,0, viewer->width() - 20, viewer->height() - 20);

    tools = new ToolsPanel( this, Qt::Tool );
    connect (tools, SIGNAL( closeToolPanel() ),
             this,  SLOT  ( close()          ) );

    connect (tools,      SIGNAL( changedTool( int ) ),
             controller, SLOT  ( setTool( int )     ) );

    connect (tools, SIGNAL( changedTool( int )  ),
             this,  SLOT  ( changeCursor( int ) ) );

    connect (tools,      SIGNAL( changedPen(QPen) ),
             controller, SLOT( setPen(QPen)       ) );

    connect( tools, SIGNAL(undo()), controller, SLOT(undo()) );
    connect( tools, SIGNAL(redo()), controller, SLOT(redo()) );
    connect( controller, SIGNAL(SignalUndoRedo(bool,bool)),
             tools, SLOT(onUndoRedoUpdated(bool,bool)) );

    connect( tools, SIGNAL(saveToFile()), this, SLOT(saveToFile()) );
    connect( tools, SIGNAL(clear()), controller, SLOT(clear()) );

    setCentralWidget( viewer );
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

void FullScreen::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save PNG picture "), "",
            tr("PNG (*.png);;All Files (*)"));
    if ( fileName.isEmpty() ) return;

    QImage image(viewer->width(), viewer->height(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    viewer->render(&painter);
    image.save(fileName);
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

