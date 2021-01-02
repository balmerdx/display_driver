#include "selectcharintervaldialog.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>


SelectCharIntervalDialog::SelectCharIntervalDialog(QWidget *parent)
    : QDialog(parent)
{
    QPushButton *addButton = new QPushButton(tr("Add"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(onAdd()));

    _firstChar = new QSpinBox();
    _firstChar->setRange(1, 65535);
    _firstChar->setValue(32);

    _countChar = new QSpinBox();
    _countChar->setRange(1, 1000);
    _countChar->setValue(1);

    QFormLayout* topLayout = new QFormLayout();
    topLayout->addRow("First char:", _firstChar);
    topLayout->addRow("Count chars:", _countChar);
    topLayout->addRow(addButton);
    setLayout(topLayout);
}

void SelectCharIntervalDialog::onAdd()
{
    done(1);
}

uint16_t SelectCharIntervalDialog::getFirstChar() const
{
    return _firstChar->value();
}

uint16_t SelectCharIntervalDialog::getCountChar() const
{
    int maxCount = 0xFFFF-_firstChar->value();

    return qMin(_countChar->value(), maxCount);
}
