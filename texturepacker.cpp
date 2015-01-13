#include "texturepacker.h"

#include <QFileInfo>
#include <QDataStream>
#include <QImage>
#include <QDebug>
#include <QBuffer>

namespace ProjectZomboidPackManager
{
    TexturePacker::TexturePacker(QObject *parent)
        : ThreadableTask(parent)
    {

    }

    TexturePacker::~TexturePacker()
    {

    }

    void TexturePacker::DoTask()
    {
        emit SendMessage("Packing Textures");
        QFileInfo dirInfo(_folder.absolutePath());

        QString folderName = dirInfo.baseName();
        QDir currentDir = _folder;
        currentDir.cdUp();\
        QFile file(currentDir.absoluteFilePath(folderName + ".pack"));

        if (file.exists())
            file.remove();

        file.open(QIODevice::WriteOnly);

        QDataStream stream(&file);
        stream.setByteOrder(QDataStream::LittleEndian);

        stream << _fileData->Pages().size();

        for (PackFilePageMetaData page : _fileData->Pages())
        {
            QString fileExtension = "";

            if (page.ImageType() == "PNG")
            {
                fileExtension = ".png";
            }
            else
            {
                fileExtension = ".dds";
            }
            if (_folder.exists(page.Name() + fileExtension))
            {
                emit SendMessage("Packing " + page.Name() + "...");

                stream << page.Name().toUtf8() << page.Entries().size()
                       << page.Mask();

                for (PackEntryMetaData entry : page.Entries())
                {
                    stream << entry.Name().toUtf8() << entry.XPos()
                           << entry.YPos() << entry.Width() << entry.Height()
                           << entry.XOffset() << entry.YOffset() << entry.TotalWidth()
                           << entry.TotalHeight();
                }
                QFile imageFile(_folder.absoluteFilePath(page.Name() + fileExtension));
                imageFile.open(QIODevice::ReadOnly);
                QByteArray imageBytes = imageFile.readAll();
                imageFile.close();

                //PZ's format adds these 4 bytes after the PNG image.
                //In Big Endian order, 0xDEADBEEF
                imageBytes.append((char)0xEF)
                        .append((char)0xBE)
                        .append((char)0xAD)
                        .append((char)0xDE);

                //DataStream adds extra data to byte arrays that isn't in
                //PZ's format. We need to write the raw bytes directly to the file.
                file.write(imageBytes);
            }
        }

        file.close();
        emit SendMessage("Finished Packing Textures");
    }

}
