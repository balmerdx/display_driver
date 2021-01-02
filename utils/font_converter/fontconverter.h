#ifndef FONTCONVERTER_H
#define FONTCONVERTER_H

#include <QObject>
class QTextStream;


struct FontToSave
{
    uint8_t height;// высота буквы
    uint8_t ascent;// высота верхней части буквы
    uint8_t char_intervals_count;//
    uint8_t bits_per_pixel; // 1 or 2 bits per pixel
};

struct CharIntervalsToSave
{
    uint16_t char_start;// начала интервала буковок в utf16 кодировке
    uint16_t char_count;// количество буковок в этом интервале
};

struct CharInfoToSave
{
    uint16_t data_offset;
    uint8_t xoffset;
    uint8_t yoffset;
    uint8_t width;
    uint8_t height;
    uint8_t xadvance;
    uint8_t pad;
};

struct CharInfo
{
    QString comment;
    CharInfoToSave info;
    std::vector<uint32_t> data;
};

struct FontData
{
    FontToSave font_header;
    std::vector<CharIntervalsToSave> intervals;
    std::vector<CharInfo> char_infos;
};


class FontConverter : public QObject
{
    Q_OBJECT
public:
    explicit FontConverter(QObject *parent = 0);

    void saveFontTest0(QFont font, QString text);
    bool saveFont(QString filename, QFont font, std::vector<CharIntervalsToSave> intervals, int bit_per_pixel);
signals:

public slots:
protected:
    void writeHex(QTextStream& stream, const void *data, size_t dataSize);

    uint32_t uint32_written;
};

#endif // FONTCONVERTER_H
