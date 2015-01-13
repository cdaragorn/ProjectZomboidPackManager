#ifndef PACKENTRYMETADATA_H
#define PACKENTRYMETADATA_H

#include <QObject>
#include <QDataStream>

namespace ProjectZomboidPackManager
{
    class PackEntryMetaData
    {

    public:
        explicit PackEntryMetaData(
                QDataStream& stream);
        PackEntryMetaData(const PackEntryMetaData& other);
        PackEntryMetaData(PackEntryMetaData&& other);
        PackEntryMetaData& operator =(const PackEntryMetaData& other);
        PackEntryMetaData& operator =(PackEntryMetaData&& other);
        ~PackEntryMetaData();

        QString Name() const { return _entryName; }
        qint32 XPos() const { return _xPos; }
        qint32 YPos() const { return _yPos; }
        qint32 Width() const { return _width; }
        qint32 Height() const { return _height; }
        qint32 XOffset() const { return _xOffset; }
        qint32 YOffset() const { return _yOffset; }
        qint32 TotalWidth() const { return _totalWidth; }
        qint32 TotalHeight() const { return _totalHeight; }

    private:
        void ReadMetaData(QDataStream& stream);

        QString _entryName;
        qint32 _xPos;
        qint32 _yPos;
        qint32 _width;
        qint32 _height;
        qint32 _xOffset;
        qint32 _yOffset;
        qint32 _totalWidth;
        qint32 _totalHeight;

    };
}

#endif // PACKENTRYMETADATA_H
