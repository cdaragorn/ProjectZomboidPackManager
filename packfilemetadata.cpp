#include "packfilemetadata.h"

#include "packfilepagemetadata.h"

#include <QFile>
#include <QDataStream>

namespace ProjectZomboidPackManager
{


    PackFileMetaData::PackFileMetaData(QString packFilePath)
    {
        _numberOfPages = 0;
        ReadMetaData(packFilePath);
    }

    PackFileMetaData::PackFileMetaData(const PackFileMetaData& other)
    {
        if (&other != this)
        {
            _numberOfPages = other._numberOfPages;
            _pages = other._pages;
        }
    }

    PackFileMetaData::PackFileMetaData(PackFileMetaData&& other)
    {
        if (&other != this)
        {
            _numberOfPages = std::move(other._numberOfPages);
            _pages = std::move(other._pages);
        }
    }

    PackFileMetaData& PackFileMetaData::operator =(const PackFileMetaData& other)
    {
        if (&other != this)
        {
            _numberOfPages = other._numberOfPages;
            _pages = other._pages;
        }

        return *this;
    }

    PackFileMetaData& PackFileMetaData::operator =(PackFileMetaData&& other)
    {
        if (&other != this)
        {
            _numberOfPages = std::move(other._numberOfPages);
            _pages = std::move(other._pages);
        }

        return *this;
    }

    PackFileMetaData::~PackFileMetaData()
    {
    }

    void PackFileMetaData::ReadMetaData(
            QString packFilePath)
    {
        QFile packFile(packFilePath);

        if (packFile.exists())
        {
            packFile.open(QIODevice::ReadOnly);
            QDataStream stream(&packFile);
            stream.setByteOrder(QDataStream::LittleEndian);

            stream >> _numberOfPages;

            for (int i = 0; i < _numberOfPages && !stream.atEnd(); ++i)
            {
                PackFilePageMetaData packPage(stream);
                _pages.push_back(std::move(packPage));
            }

            packFile.close();
        }
    }

}
