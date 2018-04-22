#ifndef MYGRAPHICSITEMS_H
#define MYGRAPHICSITEMS_H

#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class MyLine : public QGraphicsLineItem
{
public:
    MyLine( const QLineF &line, QGraphicsItem *parent = nullptr );
    virtual ~MyLine(){}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};


class MyRect : public QGraphicsRectItem
{
public:
    MyRect( const QRectF &rect, QGraphicsItem *parent = nullptr );
    MyRect( qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr );
    virtual ~MyRect(){}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};


class MyElps : public QGraphicsEllipseItem
{
public:
    MyElps( const QRectF &rect, QGraphicsItem *parent = nullptr );
    MyElps( qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr );
    virtual ~MyElps(){}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
#endif // MYGRAPHICSITEMS_H
