#ifndef GROUPSCENE_H
#define GROUPSCENE_H

#include <QList>
#include <QGraphicsScene>

#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QObject>

#include "errorclass.h"
#include "groupactionlist.h"

class ErrorClass;

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
    bool setGroupVisible( QGraphicsItemGroup* group, bool visible );

    bool deleteGroup( int index );
    bool deleteLastGroup();
    bool deleteGroupsFromIndex( int index ); //Удалить все группы от индекса до последней

    bool selectGroup( QGraphicsItemGroup* gr );
    QGraphicsItemGroup *GetSelectedGroup() { return pSelectedGroup; }

    int groupCount() const;

private:
    QList<QGraphicsItemGroup*>   groups_list;
    QGraphicsItemGroup          *pCurrentGroup;
    QGraphicsItemGroup          *pSelectedGroup;
    void set_select ( QList<QGraphicsItem*> group_items, bool sel );


protected:
    ErrorClass er;
    GroupActionList             GAList;

private slots:
    void slot_error();
    void deleteGroup( QGraphicsItemGroup* group );

public slots:
    void clear();
    void undo();
    void redo();

signals:
    void SignalError( const ErrorClass &error);
    void SignalUndoRedo( bool isUndo, bool isRedo );
};

#endif // GROUPSCENE_H
