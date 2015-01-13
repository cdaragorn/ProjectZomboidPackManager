#ifndef PACKFILEPAGEMETADATA_H
#define PACKFILEPAGEMETADATA_H

#include "packentrymetadata.h"
#include <QObject>
#include <QDataStream>
#include <vector>

namespace ProjectZomboidPackManager
{
    class PackFilePageMetaData
    {

    public:
        explicit PackFilePageMetaData(
                QDataStream& stream);
        PackFilePageMetaData(const PackFilePageMetaData& other);
        PackFilePageMetaData(PackFilePageMetaData&& other);
        PackFilePageMetaData& operator =(const PackFilePageMetaData& other);
        PackFilePageMetaData& operator =(PackFilePageMetaData&& other);
        ~PackFilePageMetaData();

        qint32 Mask() const { return _mask; }
        QString Name() const { return _pageName; }
        qint32 ImageOffset() const { return _imageStartPos; }
        qint32 ImageLength() const { return _imageByteLength; }
        QString ImageType() const { return _imageType; }
        const std::vector<PackEntryMetaData>& Entries() const { return _entries; }

    private:
        void ReadMetaData(QDataStream& stream);

        qint32 _numberOfEntries;
        qint32 _mask;
        QString _pageName;
        qint32 _imageStartPos;
        qint32 _imageByteLength;
        QString _imageType;

        std::vector<PackEntryMetaData> _entries;
    };
}

#endif // PACKFILEPAGEMETADATA_H
