#ifndef PACKMANAGERMAINWINDOW_H
#define PACKMANAGERMAINWINDOW_H

#include "packfilemetadata.h"
#include "texturemerger.h"
#include "texturepacker.h"
#include "texturesplitter.h"
#include "textureunpacker.h"

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QThread>

namespace Ui {
class PackManagerMainWindow;
}

namespace ProjectZomboidPackManager
{
    class PackManagerMainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit PackManagerMainWindow(QWidget *parent = 0);
        ~PackManagerMainWindow();

    private:
        Ui::PackManagerMainWindow *ui;
        QString _fileName;
        PackFileMetaData* _fileMetaData;

        TextureUnpacker* _unPacker;
        TextureSplitter* _splitter;
        TextureMerger* _merger;
        TexturePacker* _packer;

        QThread* _thread;

        void SetupAndRunTask(ThreadableTask* task, QDir& folder);

    public slots:
        void OnSelectFileButtonClicked();
        void OnRunButtonClicked();
        void OnThreadProcessingFinished();

        void OnSendMessage(QString message);
    };
};

#endif // PACKMANAGERMAINWINDOW_H
