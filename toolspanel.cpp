#include "toolspanel.h"
#include <QDebug>
#include <QHBoxLayout>


ToolsPanel::ToolsPanel(QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent)
{
    setWindowFlags( f );

    pBtn_pen = new QPushButton( QIcon( ":/icons/pen"  ), "", this );
    pBtn_pen->setToolTip( "Pen - drawing curves line manualy." );
    pBtn_pen->setCheckable(true);

    pBtn_brash = new QPushButton( QIcon( ":/icons/brash"  ), "", this );
    pBtn_brash->setToolTip( "Brash - marking transparent bold line." );
    pBtn_brash->setCheckable(true);

    pBtn_line = new QPushButton( QIcon( ":/icons/line"  ), "", this );
    pBtn_line->setToolTip( "Line - drawing simple line." );
    pBtn_line->setCheckable(true);

    pBtn_rect = new QPushButton( QIcon( ":/icons/rectangle"  ), "", this );
    pBtn_rect->setToolTip( "Rectangle - drawing rectangle." );
    pBtn_rect->setCheckable(true);

    pBtn_circle = new QPushButton( QIcon( ":/icons/circle"  ), "", this );
    pBtn_circle->setToolTip( "Circle - drawing circle." );
    pBtn_circle->setCheckable(true);

    pBtn_eraser = new QPushButton( QIcon( ":/icons/eraser"  ), "", this );
    pBtn_eraser->setToolTip( "Eraser - delete shapes by click." );
    pBtn_eraser->setCheckable(true);

    pBtn_undo = new QPushButton( QIcon( ":/icons/back"  ), "", this );
    pBtn_undo->setToolTip( "Undo - step back." );

    pBtn_redo = new QPushButton( QIcon( ":/icons/forward"  ), "", this );
    pBtn_redo->setToolTip( "Redo - step forward." );

    pBtn_save = new QPushButton( QIcon( ":/icons/save"  ), "", this );
    pBtn_save->setToolTip( "Save - save picture to file.");

    pBtn_clear = new QPushButton( QIcon( ":/icons/delete"  ), "", this );
    pBtn_clear->setToolTip( "Clear - delete all shapes and markers.");

    QButtonGroup *pGrouBtn = new QButtonGroup(this);
    pGrouBtn->addButton( pBtn_pen,    ToolsID::tool_pen    );
    pGrouBtn->addButton( pBtn_brash,  ToolsID::tool_brash  );
    pGrouBtn->addButton( pBtn_line,   ToolsID::tool_line   );
    pGrouBtn->addButton( pBtn_rect,   ToolsID::tool_rect   );
    pGrouBtn->addButton( pBtn_circle, ToolsID::tool_circle );
    pGrouBtn->addButton( pBtn_eraser, ToolsID::tool_eraser );
    pBtn_pen->setChecked( true );

    QHBoxLayout *lay = new QHBoxLayout( this );
    lay->addWidget( pBtn_pen    );
    lay->addWidget( pBtn_brash  );
    lay->addWidget( pBtn_line   );
    lay->addWidget( pBtn_rect   );
    lay->addWidget( pBtn_circle );
    lay->addWidget( pBtn_eraser );
    lay->addSpacing(20);
    lay->addWidget( pBtn_undo   );
    lay->addWidget( pBtn_redo   );
    lay->addWidget( pBtn_save   );
    lay->addWidget( pBtn_clear  );

    this->setLayout( lay );

    connect(pGrouBtn, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
          [=](int id, bool checked){ ToolToggled(id, checked); });

}

ToolsPanel::~ToolsPanel()
{

}

void ToolsPanel::ToolToggled(int id, bool checked)
{
    if ( checked ) emit changedTool( id );
}

void ToolsPanel::closeEvent(QCloseEvent *)
{
    emit closeToolPanel();
}
