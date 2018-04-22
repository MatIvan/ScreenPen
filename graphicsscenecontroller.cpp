#include "graphicsscenecontroller.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

GraphicsSceneController::GraphicsSceneController(QObject *parent)
    : GroupScene( parent )
{
    currentTool = ToolsID::tool_pen;

    currentPen.setColor( QColor("red") );
    currentPen.setWidth( 4 );
    currentPen.setCapStyle( Qt::RoundCap );
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
    case ToolsID::tool_line :
                            appendItemToNewGroup( get_line_firstItem() );
                            break;
    case ToolsID::tool_rect :
                            appendItemToNewGroup( get_rect_firstItem() );
                            break;
    case ToolsID::tool_circle :
                            appendItemToNewGroup( get_elips_firstItem() );
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
    case ToolsID::tool_line :
                            set_Line_Item_points(   currentItem, firstPoint, newPos );
                            break;
    case ToolsID::tool_rect :
                            set_Rect_Item_points(   currentItem, firstPoint, newPos );
                            break;
    case ToolsID::tool_circle :
                            set_Elipse_Item_points( currentItem, firstPoint, newPos );
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
    QGraphicsLineItem *temp_item;
    temp_item = new QGraphicsLineItem( QLineF( previousPoint, previousPoint ) );
    temp_item->setPen( currentPen );
    return temp_item;
}

QGraphicsItem *GraphicsSceneController::get_pen_newItem(const QPointF &newPoint)
{
    QGraphicsLineItem *temp_item;
    temp_item = new QGraphicsLineItem( QLineF( previousPoint, newPoint ) );
    temp_item->setPen( currentPen );
    return temp_item;
}

QGraphicsItem *GraphicsSceneController::get_brash_firstItem()
{
    QGraphicsLineItem *line;
    line = new QGraphicsLineItem( QLineF( previousPoint, previousPoint ) );
    QPen pen;
    pen.setWidth(16);
    pen.setColor( QColor(255,215,0,150) );
    line->setPen(pen);
    currentItem = line;
    return currentItem;
}

QGraphicsItem *GraphicsSceneController::get_line_firstItem()
{
    QGraphicsLineItem *line;
    line = new QGraphicsLineItem( QLineF( firstPoint, firstPoint ) );
    line->setPen( currentPen );
    currentItem = line;
    return currentItem;
}

QGraphicsItem *GraphicsSceneController::get_rect_firstItem()
{
    QGraphicsRectItem *rect;
    rect = new QGraphicsRectItem(firstPoint.x(), firstPoint.y(), 0, 0 );
    rect->setPen( currentPen );
    currentItem = rect;
    return currentItem;
}

QGraphicsItem *GraphicsSceneController::get_elips_firstItem()
{
    QGraphicsEllipseItem *ellipse;
    ellipse = new QGraphicsEllipseItem( firstPoint.x(), firstPoint.y(), 0, 0 );
    ellipse->setPen( currentPen );
    currentItem = ellipse;
    return currentItem;
}

void GraphicsSceneController::set_Line_Item_points( QGraphicsItem *Item, const QPointF &start, const QPointF &finish)
{
    QGraphicsLineItem *L = (QGraphicsLineItem*)(Item);
    L->setLine( QLineF( start, finish ) );
}

void GraphicsSceneController::set_Rect_Item_points(QGraphicsItem *Item, const QPointF &start, const QPointF &finish)
{
    QGraphicsRectItem *R = (QGraphicsRectItem*)(Item);
    R->setRect( QRectF( start, finish ).normalized() );
}

void GraphicsSceneController::set_Elipse_Item_points(QGraphicsItem *Item, const QPointF &start, const QPointF &finish)
{
    QGraphicsEllipseItem *E = (QGraphicsEllipseItem*)(Item);
    E->setRect( QRectF( start, finish ).normalized() );
}

void GraphicsSceneController::setTool(int id)
{
    currentTool = id;
}

void GraphicsSceneController::setPen(QPen new_pen)
{
    currentPen = new_pen;
    currentPen.setCapStyle( Qt::RoundCap );
}
