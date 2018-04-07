#include "graphicsscenecontroller.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

GraphicsSceneController::GraphicsSceneController(QObject *parent)
    : GroupScene( parent )
{

}

GraphicsSceneController::~GraphicsSceneController()
{

}

bool GraphicsSceneController::grab_desktop()
{
    QScreen *screen = QApplication::primaryScreen();
    QPixmap desktop_pixmap = screen->grabWindow(QApplication::desktop()->winId());
    QGraphicsItem *temp_item = new QGraphicsPixmapItem( desktop_pixmap );

    //TODO не понятно почему картинка смещается не ровно в начало.
    //     пришлось добавить коэффициоенты +40 и +5
    temp_item->moveBy(- desktop_pixmap.width()/2.0 +40,
                      - desktop_pixmap.height()/2.0 +5);

    return appendItemToNewGroup( temp_item );
}

void GraphicsSceneController::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *temp_item;
    temp_item = new QGraphicsEllipseItem(event->scenePos().x() - 5,
                           event->scenePos().y() - 5,
                           10,
                           10);
    appendItemToNewGroup( temp_item );
    previousPoint = event->scenePos();
}

void GraphicsSceneController::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *temp_item;
    temp_item = new QGraphicsLineItem(  previousPoint.x(),
                                        previousPoint.y(),
                                        event->scenePos().x(),
                                        event->scenePos().y());
    appendItem( temp_item );
    previousPoint = event->scenePos();
}

void GraphicsSceneController::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
