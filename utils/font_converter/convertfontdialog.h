#ifndef CONVERTFONTDIALOG_H
#define CONVERTFONTDIALOG_H

#include <QDialog>
#include "fontconverter.h"

class QPushButton;
class QLabel;
class QLineEdit;
class QListWidget;
class QComboBox;

class ConvertFontDialog : public QDialog
{
    Q_OBJECT

public:
    ConvertFontDialog(QWidget *parent = 0);
    ~ConvertFontDialog();
public slots:
    void onFinished(int result);
    void onSelectFont();
    void onConvert();
    void onSelectFilename();

    void onAddInterval();
    void onDelInterval();
    void onResetInterval();
protected:
    void setFontString();
    void updateCharInterval(int idx);
    void resetCharIntervals();
protected:
    QFont _font;
    QString _filename;
    std::vector<CharIntervalsToSave> _intervals;

    QPushButton* _selectFont;
    QLabel* _fontLabel;
    QLineEdit* _fileNameEdit;
    QPushButton* _fileNameButton;
    QListWidget* _intervalsList;

    QComboBox* _comboBitsPerPixel;

    QPushButton* _convertFont;
};

#endif // CONVERTFONTDIALOG_H
