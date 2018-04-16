#ifndef GRAPHICSSCENECONTROLLER_H
#define GRAPHICSSCENECONTROLLER_H

#include <QGraphicsSceneMouseEvent>
#include "groupscene.h"
#include "toolspanel.h"


class GraphicsSceneController : public GroupScene
{
    Q_OBJECT
public:
    GraphicsSceneController( QObject *parent = 0 );
    virtual ~GraphicsSceneController();

    bool grab_desktop();

private:
    void mousePressEvent    (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent     (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent  (QGraphicsSceneMouseEvent *);

    QGraphicsItem *get_pen_firstItem();
    QGraphicsItem *get_pen_newItem( const QPointF &newPoint );
    QGraphicsItem *get_brash_firstItem();
    QGraphicsItem *get_line_firstItem();
    QGraphicsItem *get_rect_firstItem();

    void set_Line_Item_points( QGraphicsItem *Item, const QPointF &strat, const QPointF &finish );
    void set_Rect_Item_points( QGraphicsItem *Item, const QPointF &strat, const QPointF &finish );

private:
    QPointF previousPoint;
    QPointF firstPoint;
    int currentTool;
    QGraphicsItem *currentItem;

public slots:
    void setTool( int id );
};

#endif // GRAPHICSSCENECONTROLLER_H
