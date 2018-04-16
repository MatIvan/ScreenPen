#ifndef COMBOBOXCOLOR_H
#define COMBOBOXCOLOR_H

#include <QWidget>

#include <QColor>
#include <QComboBox>

class ComboBoxColor : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBoxColor(QWidget *parent = nullptr);
    virtual ~ComboBoxColor() {}

    void addItem ( const QString &color );

private:
    QColor color;

signals:

public slots:

};

#endif // COMBOBOXCOLOR_H
