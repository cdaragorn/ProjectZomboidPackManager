#include "packentrymetadata.h"

namespace ProjectZomboidPackManager
{
    PackEntryMetaData::PackEntryMetaData(QDataStream &stream)
    {
        ReadMetaData(stream);
    }

    PackEntryMetaData::PackEntryMetaData(const PackEntryMetaData& other)
    {
        if (&other != this)
        {
            _entryName = other._entryName;
            _xPos = other._xPos;
            _yPos = other._yPos;
            _width = other._width;
            _height = other._height;
            _xOffset = other._xOffset;
            _yOffset = other._yOffset;
            _totalWidth = other._totalWidth;
            _totalHeight = other._totalHeight;
        }
    }

    PackEntryMetaData::PackEntryMetaData(PackEntryMetaData&& other)
    {
        if (&other != this)
        {
            _entryName = std::move(other._entryName);
            _xPos = std::move(other._xPos);
            _yPos = std::move(other._yPos);
            _width = std::move(other._width);
            _height = std::move(other._height);
            _xOffset = std::move(other._xOffset);
            _yOffset = std::move(other._yOffset);
            _totalWidth = std::move(other._totalWidth);
            _totalHeight = std::move(other._totalHeight);
        }

    }

    PackEntryMetaData& PackEntryMetaData::operator =(const PackEntryMetaData& other)
    {
        if (&other != this)
        {
            _entryName = other._entryName;
            _xPos = other._xPos;
            _yPos = other._yPos;
            _width = other._width;
            _height = other._height;
            _xOffset = other._xOffset;
            _yOffset = other._yOffset;
            _totalWidth = other._totalWidth;
            _totalHeight = other._totalHeight;
        }

        return *this;
    }

    PackEntryMetaData& PackEntryMetaData::operator =(PackEntryMetaData&& other)
    {
        if (&other != this)
        {
            _entryName = std::move(other._entryName);
            _xPos = std::move(other._xPos);
            _yPos = std::move(other._yPos);
            _width = std::move(other._width);
            _height = std::move(other._height);
            _xOffset = std::move(other._xOffset);
            _yOffset = std::move(other._yOffset);
            _totalWidth = std::move(other._totalWidth);
            _totalHeight = std::move(other._totalHeight);
        }

        return *this;
    }


    PackEntryMetaData::~PackEntryMetaData()
    {

    }

    void PackEntryMetaData::ReadMetaData(QDataStream &stream)
    {
        if (!stream.atEnd())
        {
            int nameLength = 0;
            stream >> nameLength;

            if (nameLength > 0 &&
                    nameLength < stream.device()->size() - stream.device()->pos())
            {
                char* nameChars = new char[nameLength];
                int bytesRead = stream.readRawData(nameChars, nameLength);

                if (bytesRead > -1)
                {
                    _entryName = QString::fromUtf8(nameChars, nameLength);

                    stream >> _xPos >> _yPos >> _width >> _height >> _xOffset >>
                            _yOffset >> _totalWidth >> _totalHeight;
                }
                delete [] nameChars;
            }
        }
    }

}
