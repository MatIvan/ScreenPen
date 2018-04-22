#ifndef GROUPACTIONLIST_H
#define GROUPACTIONLIST_H

#include <QObject>
#include <QList>

class QGraphicsItemGroup;

enum GroupActions{
    CREATE,
    DELETE
};

struct GroupAction
{
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
    void undo();
    void redo();

private:
    QList<GroupAction> MainList;
    int current_index;
    void delete_last_action();

signals:
    void delete_forever( QGraphicsItemGroup *Group );

};

#endif // GROUPACTIONLIST_H
