#include "hovergraphicsitem.h"
#include <QDebug>

HoverLine::HoverLine(const QLineF &line, QGraphicsItem *parent)
    : QGraphicsLineItem( line , parent )
{
    setAcceptHoverEvents( true );
    setFiltersChildEvents( true );
}

void HoverLine::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "HoverLine "<< event->pos();
    QGraphicsItem::hoverMoveEvent(event);
}

bool HoverLine::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    Q_UNUSED(watched);
    if(event->type() == QEvent::GraphicsSceneHoverMove)
        qDebug()<<"HoverLine "<<event;
    return false;
}
