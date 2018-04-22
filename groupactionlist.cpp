#include "groupactionlist.h"

#include <QList>

GroupActionList::GroupActionList(QObject *parent)
    : QObject(parent)
{
    current_index = 0;
}

void GroupActionList::AddGroupAction(GroupActions group_act, QGraphicsItemGroup *Group)
{
    GroupAction ga;
    ga.ActionType = group_act;
    ga.Group = Group;

    while ( MainList.size() > current_index ){
        delete_last_action();
    }

    MainList.append( ga );
    current_index = MainList.size();
}

void GroupActionList::delete_last_action()
{
    GroupAction ga = MainList.last();
    emit delete_forever( ga.Group );
    MainList.removeLast();
}

void GroupActionList::undo()
{
    //current_index--

}

void GroupActionList::redo()
{

}
