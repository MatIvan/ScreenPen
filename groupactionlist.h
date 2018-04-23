#ifndef GROUPACTIONLIST_H
#define GROUPACTIONLIST_H

#include <QObject>
#include <QList>

class QGraphicsItemGroup;

enum GroupActions{
    NOOP,
    CREATE,
    DELETE
};

struct GroupAction
{
    GroupAction( GroupActions GA = NOOP ) {ActionType = GA; }
    GroupActions ActionType;
    QGraphicsItemGroup *Group;
};

class GroupActionList : public QObject
{
    Q_OBJECT
public:
    GroupActionList( QObject *parent = nullptr);
    virtual ~GroupActionList(){}

    void AddGroupAction(GroupActions group_act, QGraphicsItemGroup *Group );
    GroupAction undo();
    GroupAction redo();

private:
    QList<GroupAction> MainList;
    int current_index;
    void delete_last_action();
    void update_state();

signals:
    void delete_forever( QGraphicsItemGroup *Group );
    void updated( bool isUndo, bool isRedo );
};

#endif // GROUPACTIONLIST_H
