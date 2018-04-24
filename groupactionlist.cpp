#include "groupactionlist.h"

#include <QList>
#include <QDebug>

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
    update_state();
    //qDebug() << "AddGroupAction > ind=" << current_index << " size=" << MainList.size();
}

void GroupActionList::delete_last_action()
{
    GroupAction ga = MainList.last();
    emit delete_forever( ga.Group );
    MainList.removeLast();
}

void GroupActionList::update_state()
{
    bool isUndo, isRedo;
    isUndo = (current_index>1);
    isRedo = (MainList.size() > current_index);
    emit updated( isUndo, isRedo );
}

GroupAction GroupActionList::undo()
{
    //qDebug() << "undo > ind=" << current_index << " size=" << MainList.size();
    if (current_index==1) return GroupAction(NOOP);
    current_index--;
    update_state();
    return MainList.at(current_index);
}

GroupAction GroupActionList::redo()
{
    //qDebug() << "redo > ind=" << current_index << " size=" << MainList.size();
    if( current_index==MainList.size() ) return GroupAction(NOOP);
    current_index++;
    update_state();
    return MainList.at(current_index-1);
}

void GroupActionList::clear()
{
    current_index = 0;
    MainList.clear();
    update_state();
}
