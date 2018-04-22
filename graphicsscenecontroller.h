#ifndef GRAPHICSSCENECONTROLLER_H
#define GRAPHICSSCENECONTROLLER_H

#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include "groupscene.h"
#include "toolspanel.h"
#include "hovergraphicsitem.h"


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
    QGraphicsItem *get_elips_firstItem();

    void set_Line_Item_points(   QGraphicsItem *Item, const QPointF &start, const QPointF &finish );
    void set_Rect_Item_points(   QGraphicsItem *Item, const QPointF &start, const QPointF &finish );
    void set_Elipse_Item_points( QGraphicsItem *Item, const QPointF &start, const QPointF &finish );

private:
    QPointF previousPoint;
    QPointF firstPoint;
    int currentTool;
    QGraphicsItem *currentItem;
    QPen currentPen;
    bool isAllowPaint;

public slots:
    void setTool( int id );
    void setPen( QPen new_pen );

};

#endif // GRAPHICSSCENECONTROLLER_H
