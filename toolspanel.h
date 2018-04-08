#ifndef TOOLSPANEL_H
#define TOOLSPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>

enum ToolsID {
    tool_non = 0,
    tool_pen,
    tool_brash,
    tool_line,
    tool_rect,
    tool_circle,
    tool_eraser
};

class ToolsPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ToolsPanel( QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags() );
    virtual ~ToolsPanel();

private:

    QButtonGroup *pGrouBtn;

    QPushButton *pBtn_pen;
    QPushButton *pBtn_brash;
    QPushButton *pBtn_line;
    QPushButton *pBtn_rect;
    QPushButton *pBtn_circle;
    QPushButton *pBtn_eraser;

    QPushButton *pBtn_undo;
    QPushButton *pBtn_redo;
    QPushButton *pBtn_save;
    QPushButton *pBtn_clear;

    void ToolToggled(int id, bool checked);

protected:
    virtual void closeEvent(QCloseEvent *) override;

signals:
    void closeToolPanel();
    void changedTool( int id );

public slots:

};

#endif // TOOLSPANEL_H
