#ifndef GROUPSCENE_H
#define GROUPSCENE_H

#include <QList>
#include <QGraphicsScene>

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QObject>

#include "errorclass.h"

class ErrorClass;

class HoverGroup : public QGraphicsItemGroup
{
public:
    HoverGroup( QGraphicsItem *parent = nullptr );
    ~HoverGroup(){}

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
};

class GroupScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GroupScene( QObject *parent = 0);
    virtual ~GroupScene();

    void newGroup();
    bool appendItem( QGraphicsItem *item );
    bool appendItemToNewGroup( QGraphicsItem *item );

    bool setGroupVisible( int index, bool visible );
    bool setGroupVisible( HoverGroup* group, bool visible );

    bool deleteGroup( HoverGroup* group);
    bool deleteGroup( int index );
    bool deleteLastGroup();
    bool deleteGroupsFromIndex( int index ); //Удалить все группы от индекса до последней

    int groupCount() const;

private:
    QList<HoverGroup*>   groups_list;
    HoverGroup          *pCurrentGroup;

protected:
    ErrorClass er;

private slots:
    void slot_error();

public slots:
    void clear();

signals:
    void SignalError( const ErrorClass &error);

};

#endif // GROUPSCENE_H
