#include "convertfontdialog.h"

#include <math.h>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontDialog>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#include <QLineEdit>
#include <QGroupBox>
#include <QListWidget>
#include <QComboBox>


#include "fontconverter.h"
#include "selectcharintervaldialog.h"


ConvertFontDialog::ConvertFontDialog(QWidget *parent)
    : QDialog(parent)
{
    _filename = "font_data.c";

    connect(this, SIGNAL(finished(int)), this, SLOT(onFinished(int)));

    _selectFont = new QPushButton("SelectFont");
    connect(_selectFont, SIGNAL(clicked()), this, SLOT(onSelectFont()));

    _fontLabel = new QLabel();

    _convertFont = new QPushButton("Convert");
    connect(_convertFont, SIGNAL(clicked()), this, SLOT(onConvert()));

    QHBoxLayout* selectFontLayout = new QHBoxLayout();
    selectFontLayout->addWidget(_fontLabel,1);
    selectFontLayout->addWidget(_selectFont);

    _fileNameEdit = new QLineEdit();
    _fileNameButton = new QPushButton("Select filename");
    connect(_fileNameButton, SIGNAL(clicked()), this, SLOT(onSelectFilename()));

    _comboBitsPerPixel = new QComboBox();
    _comboBitsPerPixel->addItem("1 bit per pixel", QVariant(1));
    _comboBitsPerPixel->addItem("2 bit per pixel", QVariant(2));

    QHBoxLayout* fileNameLayout = new QHBoxLayout();
    fileNameLayout->addWidget(_fileNameEdit);
    fileNameLayout->addWidget(_fileNameButton);

    _intervalsList = new QListWidget();
    QPushButton* addInterval = new QPushButton("Add");
    connect(addInterval, SIGNAL(clicked()), this, SLOT(onAddInterval()));
    QPushButton* delInterval = new QPushButton("Del");
    connect(delInterval, SIGNAL(clicked()), this, SLOT(onDelInterval()));
    QPushButton* resetInterval = new QPushButton("Reset");
    connect(resetInterval, SIGNAL(clicked()), this, SLOT(onResetInterval()));

    QHBoxLayout* addDelLayout = new QHBoxLayout();
    addDelLayout->addWidget(addInterval);
    addDelLayout->addWidget(delInterval);
    addDelLayout->addWidget(resetInterval);

    QVBoxLayout* intervalsLayout = new QVBoxLayout();
    intervalsLayout->addWidget(_intervalsList);
    intervalsLayout->addLayout(addDelLayout);

    QGroupBox* intervalsGroupBox = new QGroupBox("Char intervals");
    intervalsGroupBox->setLayout(intervalsLayout);

    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->addLayout(selectFontLayout);
    topLayout->addLayout(fileNameLayout);
    topLayout->addWidget(_comboBitsPerPixel);
    topLayout->addWidget(intervalsGroupBox);
    topLayout->addStretch();
    topLayout->addWidget(_convertFont);
    setLayout(topLayout);

    resetCharIntervals();

    QSettings settings;
    QString fontString = settings.value("font").toString();
    _filename = settings.value("filename", _filename).toString();

    if(!fontString.isEmpty())
        _font.fromString(fontString);
    setFontString();

    _fileNameEdit->setText(_filename);

    int idxBpp = _comboBitsPerPixel->findData(settings.value("bpp", 2).toInt());
    if(idxBpp>=0)
        _comboBitsPerPixel->setCurrentIndex(idxBpp);
}

ConvertFontDialog::~ConvertFontDialog()
{

}

void ConvertFontDialog::setFontString()
{
    QString str;
    str = _font.family();
    str += " ";
    str += QString::number(_font.pointSizeF());
    _fontLabel->setText(str);

}

void ConvertFontDialog::onFinished(int result)
{
    (void)result;
    QSettings settings;
    settings.setValue("font", _font.toString());
    settings.setValue("filename", _filename);
    settings.setValue("bpp", _comboBitsPerPixel->currentData().toInt());
}


void ConvertFontDialog::onSelectFont()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, _font, this);
    if(!ok)
        return;

    _font = font;
    setFontString();
}

void ConvertFontDialog::onConvert()
{
    FontConverter converter(this);

    if(_intervals.empty())
    {
        QMessageBox::critical(this, "", "Intervals empty");
        return;
    }

    if(!converter.saveFont(_filename, _font, _intervals, _comboBitsPerPixel->currentData().toInt()))
    {
        QMessageBox::critical(this, "", "Cannot save file : " + _filename);
    }
}

void ConvertFontDialog::onSelectFilename()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select save C filename",
                                                    _filename, "C files(*.c)");
    if(filename.isEmpty())
        return;
    _filename = filename;
    _fileNameEdit->setText(_filename);

}

void ConvertFontDialog::resetCharIntervals()
{
    _intervalsList->clear();
    _intervals.clear();

    CharIntervalsToSave interval;
    interval.char_start = 31;
    interval.char_count = 127-32;
    _intervals.push_back(interval);

    interval.char_start = L'А';
    interval.char_count = 32*2;
    _intervals.push_back(interval);

    interval.char_start = 176;
    interval.char_count = 2;
    _intervals.push_back(interval);

    for(int i=0; i<(int)_intervals.size(); i++)
    {
        _intervalsList->addItem("");
        updateCharInterval(i);
    }
}

void ConvertFontDialog::updateCharInterval(int idx)
{
    const CharIntervalsToSave& it = _intervals[idx];
    QString str;
    str.append(QChar(it.char_start));

    str += "(" + QString::number(it.char_start) + ")";

    str.append(" - ");
    str.append(QChar(it.char_start+it.char_count-1));
    str += "(" + QString::number(it.char_start+it.char_count-1) + ")";
    str += " count=" + QString::number(it.char_count);

    _intervalsList->item(idx)->setText(str);
}

void ConvertFontDialog::onResetInterval()
{
    resetCharIntervals();
}

void ConvertFontDialog::onAddInterval()
{
    SelectCharIntervalDialog dialog;
    if(!dialog.exec())
        return;

    CharIntervalsToSave interval;
    interval.char_start = dialog.getFirstChar();
    interval.char_count = dialog.getCountChar();
    _intervals.push_back(interval);

    _intervalsList->addItem("");
    updateCharInterval(_intervals.size()-1);
}

void ConvertFontDialog::onDelInterval()
{
    int idx = _intervalsList->currentRow();
    if(idx<0)
        return;

    _intervals.erase(_intervals.begin()+idx);
    delete _intervalsList->currentItem();
}
