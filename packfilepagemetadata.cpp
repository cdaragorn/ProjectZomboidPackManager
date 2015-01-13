#include "packfilepagemetadata.h"

#include <QByteArray>
#include <QByteArrayMatcher>
#include <QDebug>

namespace ProjectZomboidPackManager
{
    PackFilePageMetaData::PackFilePageMetaData(QDataStream &stream)
    {
        _numberOfEntries = 0;
        _mask = 0;
        _imageType = "Unknown";
        ReadMetaData(stream);
    }

    PackFilePageMetaData::PackFilePageMetaData(const PackFilePageMetaData& other)
    {
        if (&other != this)
        {
            _numberOfEntries = other._numberOfEntries;
            _mask = other._mask;
            _pageName = other._pageName;
            _imageStartPos = other._imageStartPos;
            _imageByteLength = other._imageByteLength;
            _entries = other._entries;
            _imageType = other._imageType;
        }
    }

    PackFilePageMetaData::PackFilePageMetaData(PackFilePageMetaData&& other)
    {
        if (&other != this)
        {
            _numberOfEntries = std::move(other._numberOfEntries);
            _mask = std::move(other._mask);
            _pageName = std::move(other._pageName);
            _imageStartPos = std::move(other._imageStartPos);
            _imageByteLength = std::move(other._imageByteLength);
            _entries = std::move(other._entries);
            _imageType = std::move(other._imageType);
        }
    }

    PackFilePageMetaData& PackFilePageMetaData::operator =(const PackFilePageMetaData& other)
    {
        if (&other != this)
        {
            _numberOfEntries = other._numberOfEntries;
            _mask = other._mask;
            _pageName = other._pageName;
            _imageStartPos = other._imageStartPos;
            _imageByteLength = other._imageByteLength;
            _entries = other._entries;
            _imageType = other._imageType;
        }

        return *this;
    }

    PackFilePageMetaData& PackFilePageMetaData::operator =(PackFilePageMetaData&& other)
    {
        if (&other != this)
        {
            _numberOfEntries = std::move(other._numberOfEntries);
            _mask = std::move(other._mask);
            _pageName = std::move(other._pageName);
            _imageStartPos = std::move(other._imageStartPos);
            _imageByteLength = std::move(other._imageByteLength);
            _entries = std::move(other._entries);
            _imageType = std::move(other._imageType);
        }

        return *this;
    }

    PackFilePageMetaData::~PackFilePageMetaData()
    {
    }

    void PackFilePageMetaData::ReadMetaData(QDataStream& stream)
    {
        if (!stream.atEnd())
        {
            qint32 nameLength = 0;
            stream >> nameLength;

            if (nameLength > 0 &&
                    nameLength < stream.device()->size() - stream.device()->pos())
            {
                char* nameChars = new char[nameLength];
                int bytesRead = stream.readRawData(nameChars, nameLength);

                if (bytesRead > -1)
                {
                    _pageName = QString::fromUtf8(nameChars, nameLength);

                    stream >> _numberOfEntries >> _mask;

                    for (int i = 0; i < _numberOfEntries && !stream.atEnd(); ++i)
                    {
                        PackEntryMetaData nextEntry(stream);
                        _entries.push_back(std::move(nextEntry));
                    }

                    //sequence indicating the end of the image file
                    QByteArray searchArray;
                    searchArray.append((char)0xEF)
                            .append((char)0xBE)
                            .append((char)0xAD)
                            .append((char)0xDE);

                    QByteArrayMatcher searchBytes(searchArray);
                    qint32 bufferSize = 1024 * 1024;
                    char* buffer = new char[bufferSize];
                    memset(buffer, 0, bufferSize);
                    qint32 numberOfBytesRead = 0;
                    _imageStartPos = stream.device()->pos();
                    QByteArray imageHeader = stream.device()->read(4);

                    if (imageHeader.at(1) == 'P' &&
                            imageHeader.at(2) == 'N' &&
                            imageHeader.at(3) == 'G')
                    {
                        _imageType = "PNG";
                    }
                    else if (imageHeader.at(0) == 'D' &&
                             imageHeader.at(1) == 'D' &&
                             imageHeader.at(2) == 'S')
                    {
                        _imageType = "DDS";
                    }
                    qint32 index = -1;

                    do
                    {
                        memset(buffer, 0, bufferSize);
                        stream.device()->seek(stream.device()->pos() - searchArray.size());
                        numberOfBytesRead = stream.readRawData(buffer, bufferSize);
                        index = searchBytes.indexIn(buffer, numberOfBytesRead);
                    }
                    while (index < 0 && numberOfBytesRead == bufferSize);

                    if (index > 0)
                    {
                        _imageByteLength = (stream.device()->pos() - (numberOfBytesRead - index) - _imageStartPos);
                        stream.device()->seek(_imageStartPos + _imageByteLength + searchArray.size());
                    }
                    delete [] buffer;
                }
                delete [] nameChars;
            }
        }
    }

}
