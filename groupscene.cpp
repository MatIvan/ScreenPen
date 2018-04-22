#include "groupscene.h"

GroupScene::GroupScene(QObject *parent)
    : QGraphicsScene( parent ),
      GAList()
{
    connect( &er,  SIGNAL( er_SignalError() ),
             this, SLOT  ( slot_error()     ) );

    connect( &GAList, SIGNAL( delete_forever( QGraphicsItemGroup* ) ),
             this, SLOT( deleteGroup( QGraphicsItemGroup* ) ) );

    er.ReturnResult( NO_error );
}

GroupScene::~GroupScene()
{

}

void GroupScene::newGroup()
{
    pCurrentGroup = createItemGroup( QList<QGraphicsItem*>() );
    pCurrentGroup->setAcceptHoverEvents( true );
    groups_list.append( pCurrentGroup );
    GAList.AddGroupAction( CREATE, pCurrentGroup );
}

bool GroupScene::appendItem(QGraphicsItem *item)
{
    if ( pCurrentGroup == NULL )
        return er.ReturnResult( IS_error, "GroupScene: Cannot append item. Have no any group was created. ");

    pCurrentGroup->addToGroup( item );
    return er.ReturnResult( NO_error );
}

bool GroupScene::appendItemToNewGroup(QGraphicsItem *item)
{
    newGroup();
    return appendItem( item );
}

bool GroupScene::setGroupVisible(int index, bool visible)
{
    if (index < 0 && index > groupCount() )
        return er.ReturnResult( IS_error , " GroupScene: Cannot set visible property. Invalid group index. ");

    setGroupVisible( groups_list.at( index ), visible );
    return er.ReturnResult( NO_error );
}

bool GroupScene::setGroupVisible(QGraphicsItemGroup *group, bool visible)
{
    if ( !groups_list.contains( group ) )
        return er.ReturnResult( IS_error , " GroupScene: Cannot set visible property. Have no this group in list. ");

    QList<QGraphicsItem*> group_items = group->childItems();
    for( int i=0; i<group_items.size(); i++ ){
        group_items.at(i)->setVisible( visible );
    }
    if (!visible){
        GAList.AddGroupAction( DELETE, group );
    }
    return er.ReturnResult( NO_error );
}

void GroupScene::deleteGroup(QGraphicsItemGroup *group)
{
    if ( !groups_list.contains( group ) )
        return;

    QList<QGraphicsItem*> group_items = group->childItems();
    for( int i=0; i<group_items.size(); i++ ){
       removeItem( group_items.at(i) );
    }
    groups_list.removeOne( group );
    destroyItemGroup( group );
}

bool GroupScene::deleteGroup(int index)
{
    if (index < 0 && index > groupCount() )
        return er.ReturnResult( IS_error , " GroupScene: Cannot delete group. Invalid group index. ");

    deleteGroup( groups_list.at( index ) );
    return er.ReturnResult( NO_error );
}

bool GroupScene::deleteLastGroup()
{
    deleteGroup( groups_list.last() );
    return true;
}

bool GroupScene::deleteGroupsFromIndex(int index)
{
    if (index < 0 && index > groupCount() )
        return er.ReturnResult( IS_error , " GroupScene: Cannot delete groups from index. Invalid group index. ");

    while ( index < groupCount() )
    {
        deleteLastGroup();
    }
    return er.ReturnResult( NO_error );
}

bool GroupScene::selectGroup(QGraphicsItemGroup *gr)
{
    bool result = false;

    if (pSelectedGroup){
        set_select( pSelectedGroup->childItems(), false );
        result = true;
    }
    pSelectedGroup = gr;
    if (gr == 0) return result;
    set_select( pSelectedGroup->childItems(), true );
    result = true;

    return result;
}

int GroupScene::groupCount() const
{
    return groups_list.size();
}

void GroupScene::set_select(QList<QGraphicsItem *> group_items, bool sel)
{
    for( int i=0; i<group_items.size(); i++ ){
       group_items.at(i)->setData( 1, sel );
    }
}

void GroupScene::slot_error()
{
    emit SignalError( er );
}

void GroupScene::clear()
{
    deleteGroupsFromIndex(0);
    QGraphicsScene::clear();
}

void GroupScene::undo()
{
    GAList.undo();
}

void GroupScene::redo()
{
    GAList.redo();
}
