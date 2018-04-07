#include "graphicsscenecontroller.h"
#include <QDebug>

GraphicsSceneController::GraphicsSceneController(QObject *parent)
    : GroupScene( parent )
{

}

GraphicsSceneController::~GraphicsSceneController()
{

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
