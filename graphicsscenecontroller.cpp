#include "graphicsscenecontroller.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

GraphicsSceneController::GraphicsSceneController(QObject *parent)
    : GroupScene( parent )
{
    currentTool = ToolsID::tool_pen;
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
    firstPoint = event->scenePos();
    previousPoint = firstPoint;

    switch( currentTool ){
    case ToolsID::tool_pen :
                            appendItemToNewGroup( get_pen_firstItem() );
                            break;
    case ToolsID::tool_brash :
                            appendItemToNewGroup( get_brash_firstItem() );
                            break;
    default:
        er.ReturnResult( IS_error, "GraphicsSceneController: Start drawing: Invalid tool.");
    }

}

void GraphicsSceneController::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF newPos = event->scenePos();

    switch( currentTool ){
    case ToolsID::tool_pen :
                            appendItem( get_pen_newItem( newPos ) );
                            break;
    case ToolsID::tool_brash :
                            removeItem( currentItem );
                            appendItem( get_barsh_newItem( newPos ) );
                            break;
    default:
        er.ReturnResult( IS_error, "GraphicsSceneController: Drawing in process: Invalid tool.");
    }


    previousPoint = event->scenePos();
}

void GraphicsSceneController::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

}

QGraphicsItem *GraphicsSceneController::get_pen_firstItem()
{
    QGraphicsItem *temp_item;
    temp_item = new QGraphicsLineItem( previousPoint.x(),     previousPoint.y(),
                                       previousPoint.x() + 1, previousPoint.y() + 1);
    return temp_item;
}

QGraphicsItem *GraphicsSceneController::get_pen_newItem(const QPointF &newPoint)
{
    QGraphicsItem *temp_item;
    temp_item = new QGraphicsLineItem( previousPoint.x(), previousPoint.y(),
                                       newPoint.x(),      newPoint.y() );
    return temp_item;
}

QGraphicsItem *GraphicsSceneController::get_brash_firstItem()
{
    QGraphicsLineItem *line;
    line = new QGraphicsLineItem(firstPoint.x(),   firstPoint.y(),
                                 firstPoint.x()+1, firstPoint.y()+1 );
    QPen pen;
    pen.setWidth(16);
    pen.setColor( QColor(0,0,0,100) );
    line->setPen(pen);
    currentItem = line;
    return currentItem;
}

QGraphicsItem *GraphicsSceneController::get_barsh_newItem(const QPointF &newPoint)
{
    QGraphicsLineItem *line;
    line = new QGraphicsLineItem(firstPoint.x(), firstPoint.y(),
                                 newPoint.x(),   newPoint.y() );
    QPen pen;
    pen.setWidth(16);
    pen.setColor( QColor(0,0,0,100) );
    line->setPen(pen);
    currentItem = line;
    return currentItem;
}

void GraphicsSceneController::setTool(int id)
{
    currentTool = id;
}
