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
    void mouseReleaseEvent  (QGraphicsSceneMouseEvent *event);

private:
    QPointF previousPoint;
    int currentTool;

public slots:
    void setTool( int id );
};

#endif // GRAPHICSSCENECONTROLLER_H
