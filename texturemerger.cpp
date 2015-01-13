#include "texturemerger.h"

#include "packentrymetadata.h"

#include <QImage>
#include <QPainter>

namespace ProjectZomboidPackManager
{
    TextureMerger::TextureMerger(QObject *parent)
        : ThreadableTask(parent)
    {

    }

    TextureMerger::~TextureMerger()
    {

    }

    void TextureMerger::DoTask()
    {
        QStringList filters;
        filters << "*.png";
        QDir currentDir = _folder;

        for (PackFilePageMetaData data : _fileData->Pages())
        {
            emit SendMessage("Merging " + data.Name());
            if (currentDir.exists(data.Name()) &&
                    currentDir.exists(data.Name() + ".png"))
            {
                QString imageFilePath = currentDir.absolutePath() + "/" + data.Name() + ".png";
                QImage image(imageFilePath);
                QImage newImage(image.width(), image.height(), image.format());
                QPainter painter(&newImage);
                currentDir.remove(imageFilePath);
                currentDir.cd(data.Name());

                for (PackEntryMetaData entry : data.Entries())
                {
                    if (currentDir.exists(entry.Name() + ".png"))
                    {
                        QImage texture(currentDir.absolutePath() + "/" + entry.Name() + ".png");
                        painter.drawImage(entry.XPos(), entry.YPos(), texture);
                    }
                }
                newImage.save(imageFilePath);
                currentDir.cdUp();
            }
        }
        emit SendMessage("Finished merging all files.");
    }

}
