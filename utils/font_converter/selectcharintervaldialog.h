#ifndef SELECTCHARINTERVALDIALOG_H
#define SELECTCHARINTERVALDIALOG_H

#include <QDialog>

class QSpinBox;

class SelectCharIntervalDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectCharIntervalDialog(QWidget *parent = 0);

    uint16_t getFirstChar() const;
    uint16_t getCountChar() const;
signals:

public slots:
    void onAdd();
protected:

    QSpinBox* _firstChar;
    QSpinBox* _countChar;
};

#endif // SELECTCHARINTERVALDIALOG_H
