#include "mygraphicsitems.h"
#include <QPainter>

MyLine::MyLine(const QLineF &line, QGraphicsItem *parent)
    : QGraphicsLineItem( line, parent )
{
    setData(1, QVariant( false ) );
}

void MyLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( data(1).toBool() ){
        QPen P;
        P.setColor( Qt::black );
        P.setWidth( pen().width()+4 );
        painter->setPen( P );
        painter->drawLine( line() );
    }
    QGraphicsLineItem::paint(painter,option,widget);
}

MyRect::MyRect(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem( rect, parent )
{
    setData(1, QVariant( false ) );
}

MyRect::MyRect(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsRectItem( x, y, width, height, parent )
{
    setData(1, QVariant( false ) );
}

void MyRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( data(1).toBool() ){
        QPen P;
        P.setColor( Qt::black );
        P.setWidth( pen().width()+4 );
        painter->setPen( P );
        painter->drawRect( rect() );
    }
    QGraphicsRectItem::paint(painter,option,widget);
}


MyElps::MyElps(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem( rect, parent )
{
    setData(1, QVariant( false ) );
}

MyElps::MyElps(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsEllipseItem( x, y, width, height, parent )
{
    setData(1, QVariant( false ) );
}

void MyElps::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( data(1).toBool() ){
        QPen P;
        P.setColor( Qt::black );
        P.setWidth( pen().width()+4 );
        painter->setPen( P );
        painter->drawEllipse( rect() );
    }
    QGraphicsEllipseItem::paint(painter,option,widget);
}
