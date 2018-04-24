#include "toolspanel.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>

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

    pCBC_color = new ComboBoxColor(this);
    pCBC_color->setToolTip( "Color - select pen color." );

    pCB_width = new QComboBox(this);
    pCB_width->setToolTip( "Width - select pen width." );
    pCB_width->addItem(" 2 px", QVariant(  2 ));
    pCB_width->addItem(" 4 px", QVariant(  4 ));
    pCB_width->addItem(" 8 px", QVariant(  8 ));
    pCB_width->addItem("12 px", QVariant( 12 ));
    pCB_width->addItem("16 px", QVariant( 16 ));
    pCB_width->addItem("20 px", QVariant( 20 ));
    pCB_width->setCurrentIndex(1);

    QButtonGroup *pGrouBtn = new QButtonGroup(this);
    pGrouBtn->addButton( pBtn_pen,    ToolsID::tool_pen    );
    pGrouBtn->addButton( pBtn_brash,  ToolsID::tool_brash  );
    pGrouBtn->addButton( pBtn_line,   ToolsID::tool_line   );
    pGrouBtn->addButton( pBtn_rect,   ToolsID::tool_rect   );
    pGrouBtn->addButton( pBtn_circle, ToolsID::tool_circle );
    pGrouBtn->addButton( pBtn_eraser, ToolsID::tool_eraser );
    pBtn_pen->setChecked( true );

    QVBoxLayout *V_lay_1 = new QVBoxLayout( this );

    QHBoxLayout *H_lay_1 = new QHBoxLayout( this );
    H_lay_1->addWidget( pBtn_pen    );
    H_lay_1->addWidget( pBtn_brash  );
    H_lay_1->addWidget( pBtn_line   );
    H_lay_1->addWidget( pBtn_rect   );
    H_lay_1->addWidget( pBtn_circle );
    H_lay_1->addWidget( pBtn_eraser );
    H_lay_1->addSpacing(20);
    H_lay_1->addWidget( pBtn_undo   );
    H_lay_1->addWidget( pBtn_redo   );
    H_lay_1->addWidget( pBtn_save   );
    H_lay_1->addWidget( pBtn_clear  );

    QHBoxLayout *H_lay_2 = new QHBoxLayout( this );
    H_lay_2->addWidget( pCBC_color );
    H_lay_2->addWidget( pCB_width  );
    H_lay_2->addStretch();

    V_lay_1->addLayout( H_lay_1 );
    V_lay_1->addLayout( H_lay_2 );

    setLayout( V_lay_1 );

    connect(pGrouBtn, QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
          [=](int id, bool checked){ ToolToggled(id, checked); });
    connect(pCBC_color, SIGNAL(currentTextChanged(QString)) ,
            this, SLOT(PenChanged()) );
    connect(pCB_width , SIGNAL(currentTextChanged(QString)) ,
            this, SLOT(PenChanged()) );
    connect(pBtn_undo, SIGNAL(clicked()),
            this, SIGNAL( undo()) );
    connect(pBtn_redo, SIGNAL(clicked()),
            this, SIGNAL(redo()) );
    connect(pBtn_save, SIGNAL(clicked()),
            this, SIGNAL(saveToFile()));
    connect(pBtn_clear, SIGNAL(clicked()), this, SIGNAL(clear()) );
}

ToolsPanel::~ToolsPanel()
{

}

void ToolsPanel::ToolToggled(int id, bool checked)
{
    if ( checked ) emit changedTool( id );
}

void ToolsPanel::PenChanged()
{
    QPen pen;
    pen.setColor( QColor( pCBC_color->currentText() ) );
    pen.setWidth( pCB_width->currentData().toInt() );

    emit changedPen( pen );
}

void ToolsPanel::onUndoRedoUpdated(bool isUndo, bool isRedo)
{
    pBtn_undo->setEnabled( isUndo );
    pBtn_redo->setEnabled( isRedo );
}

void ToolsPanel::closeEvent(QCloseEvent *)
{
    emit closeToolPanel();
}

