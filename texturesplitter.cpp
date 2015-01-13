#include "texturesplitter.h"

#include <QImage>
#include <QThread>

namespace ProjectZomboidPackManager
{
    TextureSplitter::TextureSplitter(QObject *parent)
        : ThreadableTask(parent)
    {

    }

    TextureSplitter::~TextureSplitter()
    {

    }

    void TextureSplitter::DoTask()
    {
        emit SendMessage("Splitting Textures!");
        QStringList filters;
        filters << "*.png";

        QFileInfoList files = _folder.entryInfoList(
                    filters,
                    QDir::Files | QDir::NoDotAndDotDot,
                    QDir::Name);

        for (QFileInfo next : files)
        {
            emit SendMessage("Splitting " + next.fileName() + "...");

            for (PackFilePageMetaData data : _fileData->Pages())
            {
                if (data.Name() == next.baseName())
                {
                    QImage image(next.absoluteFilePath());
                    QDir folderToSaveTo = _folder;
                    folderToSaveTo.mkdir(next.baseName());
                    folderToSaveTo.cd(next.baseName());

                    for (PackEntryMetaData entry : data.Entries())
                    {
                        QRect rect(entry.XPos(),
                                   entry.YPos(),
                                   entry.Width(), entry.Height());

                        QImage texture = image.copy(rect);
                        texture.save(folderToSaveTo.absolutePath() + "/" + entry.Name() + ".png");
                    }
                    break;
                }
            }
            QThread::msleep(0);
        }
        emit SendMessage("Finished Splitting Textures");
    }

}
