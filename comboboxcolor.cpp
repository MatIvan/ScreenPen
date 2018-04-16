#include "comboboxcolor.h"
#include <QPixmap>

ComboBoxColor::ComboBoxColor(QWidget *parent)
    : QComboBox(parent)
{
    addItem( "black" );
    addItem( "white" );
    addItem( "blue" );
    addItem( "red" );
    addItem( "green" );
    addItem( "gold" );

    setCurrentIndex(3);
}

void ComboBoxColor::addItem(const QString &color)
{
    QPixmap pix(64,32);
    pix.fill( QColor( color ) );
    QComboBox::addItem( QIcon(pix), color );
}
