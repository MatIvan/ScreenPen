#ifndef HOVERGRAPHICSITEM_H
#define HOVERGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>


class HoverLine : public QGraphicsLineItem
{
public:
    HoverLine( const QLineF &line, QGraphicsItem *parent = nullptr );
    virtual ~HoverLine() {}

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

};


#endif // HOVERGRAPHICSITEM_H
