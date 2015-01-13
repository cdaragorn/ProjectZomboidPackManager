#include "textureunpacker.h"

#include <QFileInfo>

namespace ProjectZomboidPackManager
{
    TextureUnpacker::TextureUnpacker(QObject *parent)
        : ThreadableTask(parent)
    {

    }

    TextureUnpacker::~TextureUnpacker()
    {

    }

    void TextureUnpacker::DoTask()
    {
        QFileInfo dirInfo(_folder.absolutePath());
        QDir currentDir = _folder;
        currentDir.cdUp();
        emit SendMessage("Unpacking " + dirInfo.baseName() + ".pack");

        if (currentDir.exists(dirInfo.baseName() + ".pack"))
        {
            QFile file(currentDir.absoluteFilePath(dirInfo.baseName() + ".pack"));
            if (file.open(QIODevice::ReadOnly))
            {
                currentDir.cd(dirInfo.baseName());
                for (quint32 i = 0; i < _fileData->Pages().size(); ++i)
                {
                    PackFilePageMetaData nextPage = _fileData->Pages().at(i);
                    QString fileExtension = "";
                    if (nextPage.ImageType() == "PNG")
                    {
                        fileExtension = ".png";
                    }
                    else if (nextPage.ImageType() == "DDS")
                    {
                        fileExtension = ".dds";
                    }
                    QString imageName = nextPage.Name();

                    emit SendMessage("Unpacking " + imageName + "...");

                    QFile imageFile(currentDir.absolutePath() + "/" + imageName + fileExtension);
                    imageFile.open(QIODevice::WriteOnly);

                    file.seek(nextPage.ImageOffset());
                    imageFile.write(file.read(nextPage.ImageLength()));
                    imageFile.close();
                }
                file.close();
            }
        }
        emit SendMessage("Finished Unpacking " + dirInfo.baseName() + ".pack");
    }

}
