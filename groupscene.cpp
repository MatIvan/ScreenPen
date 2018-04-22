#include "groupscene.h"
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

GroupScene::GroupScene(QObject *parent)
    : QGraphicsScene( parent )
{
    connect( &er,  SIGNAL( er_SignalError() ),
             this, SLOT  ( slot_error()     ) );

    er.ReturnResult( NO_error );
}

GroupScene::~GroupScene()
{

}

void GroupScene::newGroup()
{
    pCurrentGroup = (HoverGroup*)( createItemGroup( QList<QGraphicsItem*>() ) );
    pCurrentGroup->setAcceptHoverEvents(true);
    pCurrentGroup->setFiltersChildEvents( true );
    groups_list.append( pCurrentGroup );
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

bool GroupScene::setGroupVisible(HoverGroup *group, bool visible)
{
    if ( !groups_list.contains( group ) )
        return er.ReturnResult( IS_error , " GroupScene: Cannot set visible property. Have no this group in list. ");

    QList<QGraphicsItem*> group_items = group->childItems();
    for( int i=0; i<group_items.size(); i++ ){
        group_items.at(i)->setVisible( visible );
    }
    return er.ReturnResult( NO_error );
}

bool GroupScene::deleteGroup(HoverGroup *group)
{
    if ( !groups_list.contains( group ) )
        return er.ReturnResult( IS_error , " GroupScene: Cannot delete group. Have no this group in list. ");

    QList<QGraphicsItem*> group_items = group->childItems();
    for( int i=0; i<group_items.size(); i++ ){
       removeItem( group_items.at(i) );
    }
    groups_list.removeOne( group );
    destroyItemGroup( group );
    return er.ReturnResult( NO_error );
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
    return deleteGroup( groups_list.last() );
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

int GroupScene::groupCount() const
{
    return groups_list.size();
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

HoverGroup::HoverGroup(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent)
{
    setAcceptHoverEvents( true );
    setFiltersChildEvents( true );
}

void HoverGroup::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "HoverGroup "<< event->pos();
    QGraphicsItem::hoverMoveEvent(event);
}

bool HoverGroup::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if(event->type() == QEvent::GraphicsSceneHoverMove)
        qDebug()<<"HoverGroup "<<event;
    return false;
}

