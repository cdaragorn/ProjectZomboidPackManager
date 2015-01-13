#ifndef PACKFILEMETADATA_H
#define PACKFILEMETADATA_H

#include "packfilepagemetadata.h"

#include <QObject>
#include <QString>
#include <vector>

namespace ProjectZomboidPackManager
{
    class PackFileMetaData
    {
    public:
        explicit PackFileMetaData(QString packFilePath);
        PackFileMetaData(const PackFileMetaData& other);
        PackFileMetaData(PackFileMetaData&& other);
        PackFileMetaData& operator =(const PackFileMetaData& other);
        PackFileMetaData& operator =(PackFileMetaData&& other);
        ~PackFileMetaData();

        const std::vector<PackFilePageMetaData>& Pages() const { return _pages; }

    private:
        qint32 _numberOfPages;
        std::vector<PackFilePageMetaData> _pages;
        void ReadMetaData(QString packFilePath);
    };
};

#endif // PACKFILEMETADATA_H
