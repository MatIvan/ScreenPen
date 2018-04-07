#ifndef GRAPHICSSCENECONTROLLER_H
#define GRAPHICSSCENECONTROLLER_H

#include <QGraphicsSceneMouseEvent>
#include "groupscene.h"


class GraphicsSceneController : public GroupScene
{
    Q_OBJECT
public:
    GraphicsSceneController( QObject *parent = 0 );
    virtual ~GraphicsSceneController();

private:
    void mousePressEvent    (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent     (QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent  (QGraphicsSceneMouseEvent *event);

private:
    QPointF previousPoint;

};

#endif // GRAPHICSSCENECONTROLLER_H
