#include "fontconverter.h"

#include <QRawFont>
#include <QImage>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <stdint.h>
#include <math.h>

int paletteFromGray(uint8_t gray)
{
    if(gray<60)
        return 0;
    if(gray<130)
        return 1;
    if(gray<200)
        return 2;
    return 3;
}

uint8_t paletteToGray(int idx)
{
    if(idx==0)
        return 0;
    if(idx==1)
        return 100;
    if(idx==2)
        return 180;
    return 255;
}


FontConverter::FontConverter(QObject *parent) : QObject(parent)
{

}

void FontConverter::saveFontTest0(QFont font, QString text)
{
    QRawFont rawFont = QRawFont::fromFont(font);
    QFontMetrics fontMetrics(font);

    QVector<quint32> glyphs = rawFont.glyphIndexesForString(text);
    QVector<QPointF> advances = rawFont.advancesForGlyphIndexes(glyphs, QRawFont::SeparateAdvances);

    QImage image(256, fontMetrics.height()+1, QImage::Format_ARGB32);
    image.fill(QColor(0, 0, 0));

    {
        QPainter qPainter(&image);
        qPainter.setBrush(Qt::NoBrush);
        qPainter.setFont(font);

        QBrush brush(QColor(255,255,255));
        float x = 0;
        float y = rawFont.ascent();

        qPainter.setPen(Qt::white);
        qPainter.drawText(x, y, text);
        //qPainter.setPen(Qt::green);
        //qPainter.drawLine(0, fontMetrics.height(), 100, fontMetrics.height());

/*
        for(int i=0; i<glyphs.size(); i++)
        {
            QPointF advance = advances[i];

            //quint32 glyph = glyphs[i];
            //QPainterPath path = rawFont.pathForGlyph(glyph);
            //QImage image = rawFont.alphaMapForGlyph(glyph, QRawFont::PixelAntialiasing);
            //QString outname = QString::number(glyph)+".png";
            //image.save(outname);

            //QRect charRect = fontMetrics.boundingRect(text[i]);
            //qPainter.drawImage(x, y+charRect.y(), image);
            qPainter.setPen(Qt::red);
            qPainter.drawText(x, y, QString(text[i]));
            qPainter.setPen(Qt::blue);
            //qPainter.drawRect(charRect.x()+x, charRect.y()+y, charRect.width(), charRect.height());

            x += advance.x();

            //qPainter.translate(QPointF(p.x(), p.y() + i*0));
            //qPainter.fillPath(path, brush);
        }
*/
    }

    //quantize image
    for(int y=0; y<image.height(); y++)
    for(int x=0; x<image.width(); x++)
    {
        QRgb color = image.pixel(x,y);
        uint8_t gray =paletteToGray(paletteFromGray(qGreen(color)));

        image.setPixel(x, y, qRgb(gray, gray, gray));
    }

    image.save("out.png");
}

bool FontConverter::saveFont(QString filename, QFont font,  std::vector<CharIntervalsToSave> intervals, int bit_per_pixel)
{
    uint32_written = 0;
    QRawFont rawFont = QRawFont::fromFont(font);
    QFontMetrics fontMetrics(font);

    QImage image(fontMetrics.maxWidth(), fontMetrics.height()+1, QImage::Format_ARGB32);
    image.fill(Qt::black);

    FontData fdata;
    fdata.font_header.height = fontMetrics.height();
    fdata.font_header.ascent = rawFont.ascent();
    fdata.font_header.char_intervals_count = intervals.size();
    fdata.font_header.bits_per_pixel = bit_per_pixel;
    fdata.intervals = intervals;

    if(fdata.font_header.bits_per_pixel==1)
        font.setStyleStrategy(QFont::NoAntialias);


    uint32_t chars_count = 0;
    for(const CharIntervalsToSave& it : intervals)
    {
        chars_count += it.char_count;
    }

    //char_data_offset - Считаем в uint32_t числах. offset от начала файла, в который пишется текущий char.
    uint32_t char_data_offset = sizeof(FontToSave)+sizeof(CharIntervalsToSave)*intervals.size()+sizeof(CharInfoToSave)*chars_count;
    Q_ASSERT(char_data_offset%4==0);
    char_data_offset /= 4;

    //31 это у нас пробел шириной в цифру

    for(size_t itrv = 0; itrv<intervals.size(); itrv++)
    {
        QString text;
        CharIntervalsToSave& its = intervals[itrv];
        for(int c=its.char_start; c<its.char_start+its.char_count; c++)
        {
            if(c==31)
            {
                text.append(QChar((ushort)32));
                continue;
            }

            text.append(QChar((ushort)c));
        }

        QVector<quint32> glyphs = rawFont.glyphIndexesForString(text);
        QVector<QPointF> advances = rawFont.advancesForGlyphIndexes(glyphs, QRawFont::SeparateAdvances);
        for(int i=0; i<text.size(); i++)
        {
            CharInfo info;
            QTextStream comment_stream(&info.comment);

            float xadvance = advances[i].x();

            if(its.char_start+i==31)
            {
                //Это у нас пробел широкий
                QVector<quint32> glyphs = rawFont.glyphIndexesForString(QString("0"));
                QVector<QPointF> advances = rawFont.advancesForGlyphIndexes(glyphs, QRawFont::SeparateAdvances);
                xadvance = advances[0].x();
            }

            QRect charRect = fontMetrics.boundingRect(text[i]);
            Q_ASSERT(charRect.bottom() <= fontMetrics.height());

            if(charRect.left()<0)
            {
                charRect.setLeft(0);
            }

            if(charRect.right() > fontMetrics.maxWidth())
            {
                charRect.setRight(fontMetrics.maxWidth());
            }

            QPainter qPainter(&image);
            qPainter.setBrush(Qt::NoBrush);
            qPainter.setFont(font);
            image.fill(Qt::black);
            qPainter.setPen(Qt::white);
            qPainter.drawText(0, rawFont.ascent(), QString(text[i]));
            qPainter.end();
            comment_stream << "//char='" << text[i] << "'";
            comment_stream << " offset=(" << charRect.left() << ", " << charRect.top()+rawFont.ascent() << ")";
            comment_stream << " width=" << charRect.width();
            comment_stream << " height=" << charRect.height();
            comment_stream << " xadvance=" << xadvance;
            comment_stream << endl;

            info.info.data_offset = char_data_offset;
            info.info.xoffset = charRect.left();
            info.info.yoffset = charRect.top()+rawFont.ascent();
            info.info.width = charRect.width();
            info.info.height = charRect.height();
            info.info.xadvance = lroundf(xadvance);
            info.info.pad = 0;

            if(fdata.font_header.bits_per_pixel==1)
            {
                std::vector<bool> pixels;
                for(int y=0; y<charRect.height(); y++)
                {
                    comment_stream << "//";
                    for(int x=0; x<charRect.width(); x++)
                    {
                        QRgb color = image.pixel(x+charRect.left(), y+charRect.top()+rawFont.ascent());
                        bool on = qGreen(color)?true:false;
                        pixels.push_back(on);
                        comment_stream << (on?'X':'.');
                    }
                    comment_stream << endl;
                }
                //pixels to bits
                std::vector<uint32_t>& pixels32 = info.data;
                uint32_t data32 = 0;
                int bits_filled = 0;
                for(bool on : pixels)
                {
                    if(on)
                        data32 |= uint32_t(1)<<bits_filled;

                    bits_filled++;

                    if(bits_filled==32)
                    {
                        pixels32.push_back(data32);
                        data32 = 0;
                        bits_filled = 0;
                    }
                }

                if(bits_filled)
                    pixels32.push_back(data32);
            } else
            {
                //2 bits per pixels
                std::vector<uint8_t> pixels;
                for(int y=0; y<charRect.height(); y++)
                {
                    comment_stream << "//";
                    for(int x=0; x<charRect.width(); x++)
                    {
                        QRgb color = image.pixel(x+charRect.left(), y+charRect.top()+rawFont.ascent());
                        uint8_t on = paletteFromGray(qGreen(color));
                        pixels.push_back(on);

                        switch(on)
                        {
                        case 0: comment_stream << '.'; break;
                        case 1: comment_stream << 'o'; break;
                        case 2: comment_stream << 'O'; break;
                        case 3: comment_stream << 'W'; break;
                        default:;
                        }

                    }
                    comment_stream << endl;
                }
                //pixels to bits
                std::vector<uint32_t>& pixels32 = info.data;
                uint32_t data32 = 0;
                int bits_filled = 0;
                for(uint32_t on : pixels)
                {
                    data32 |= on<<bits_filled;

                    bits_filled += 2;

                    if(bits_filled==32)
                    {
                        pixels32.push_back(data32);
                        data32 = 0;
                        bits_filled = 0;
                    }
                }

                if(bits_filled)
                    pixels32.push_back(data32);
            }

            char_data_offset += info.data.size();

            fdata.char_infos.push_back(info);
        }
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text))
        return false;
    QTextStream file_stream(&file);
    file_stream << "// family=" << font.family() << " size=" << font.pointSizeF() << endl;
    file_stream << "// height=" << fdata.font_header.height << endl;
    file_stream << "// bytes count=" << char_data_offset*4 << "  bits_per_pixel=" << fdata.font_header.bits_per_pixel <<endl;

    file_stream << "const uint32_t font_data["<< char_data_offset << "]= {" << endl;

    writeHex(file_stream, &fdata.font_header, sizeof(fdata.font_header));

    for(const CharIntervalsToSave& it : intervals)
    {
        file_stream << "// start char =" << it.char_start << " count=" << it.char_count << endl;
        writeHex(file_stream, &it, sizeof(it));
    }

    file_stream << "// char infos count=" << chars_count << endl;
    for(const CharInfo& info : fdata.char_infos)
    {
        writeHex(file_stream, &info.info, sizeof(info.info));
    }

    for(const CharInfo& info : fdata.char_infos)
    {
        file_stream << info.comment;
        writeHex(file_stream, info.data.data(), info.data.size()*4);
    }

    file_stream << "};" << endl;

    Q_ASSERT(char_data_offset==uint32_written);
    return true;
}

void FontConverter::writeHex(QTextStream& stream, const void* data, size_t dataSize)
{
    Q_ASSERT(dataSize%4==0);
    for(size_t i=0; i<dataSize/4; i++)
    {
        uint32_t d = ((uint32_t*)data)[i];
        stream << "0x" <<QString::number(d, 16) <<", ";
        uint32_written++;
    }
    stream << endl;
}
