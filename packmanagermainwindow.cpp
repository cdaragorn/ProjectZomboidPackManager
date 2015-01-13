#include "packmanagermainwindow.h"
#include "ui_packmanagermainwindow.h"
#include "packfilemetadata.h"

#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QFileInfo>

namespace ProjectZomboidPackManager
{
    PackManagerMainWindow::PackManagerMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::PackManagerMainWindow),
        _fileMetaData(nullptr),
        _splitter(nullptr),
        _merger(nullptr)
    {
        ui->setupUi(this);

        connect(this->ui->SelectPackFileButton,
                    SIGNAL(clicked()),
                    this,
                    SLOT(OnSelectFileButtonClicked()));

        connect(this->ui->RunButton,
                    SIGNAL(clicked()),
                    this,
                    SLOT(OnRunButtonClicked()));
    }

    PackManagerMainWindow::~PackManagerMainWindow()
    {
        delete ui;

        if (_fileMetaData != nullptr)
            delete _fileMetaData;
    }

    void PackManagerMainWindow::OnSelectFileButtonClicked()
    {
        QString file = QFileDialog::getOpenFileName(this, "Choose .pack file");

        if (!file.isNull() && !file.isEmpty())
        {
            QFile theFile(file);

            if (theFile.exists())
            {
                _fileName = theFile.fileName();
                ui->PackFilePathLineEdit->setText(_fileName);

                if (_fileMetaData != NULL)
                    delete _fileMetaData;

                _fileMetaData = new PackFileMetaData(_fileName);
            }
        }
    }

    void PackManagerMainWindow::SetupAndRunTask(ThreadableTask* task, QDir& folder)
    {
        _thread = new QThread(this);

        task->Prepare(folder, *_fileMetaData);

        connect(task,
                SIGNAL(SendMessage(QString)),
                this,
                SLOT(OnSendMessage(QString)));

        connect (task,
                 SIGNAL(FinishedTask()),
                 this,
                 SLOT(OnThreadProcessingFinished()));

        connect(_thread,
                SIGNAL(started()),
                task,
                SLOT(Run()));

        connect(_thread,
                SIGNAL(finished()),
                _thread,
                SLOT(deleteLater()));

        connect(_thread,
                SIGNAL(finished()),
                task,
                SLOT(deleteLater()));

        task->moveToThread(_thread);

        _thread->start();
    }

    void PackManagerMainWindow::OnRunButtonClicked()
    {
        if (ui->PackRadioButton->isChecked())
        {
            ui->RunButton->setEnabled(false);
            _packer = new TexturePacker();

            QFileInfo fileInfo(_fileName);
            QDir folder = fileInfo.absoluteDir();
            folder.cd(fileInfo.baseName());

            SetupAndRunTask(_packer, folder);
        }
        else if (ui->UnpackRadioButton->isChecked())
        {
            ui->RunButton->setEnabled(false);
            _unPacker = new TextureUnpacker();
            QFileInfo fileInfo(_fileName);

            QDir thisDir = fileInfo.absoluteDir();
            thisDir.mkdir(fileInfo.baseName());
            thisDir.cd(fileInfo.baseName());

            SetupAndRunTask(_unPacker, thisDir);
        }
        else if (ui->SplitRadioButton->isChecked())
        {
            ui->RunButton->setEnabled(false);
            _splitter = new TextureSplitter();

            QFileInfo fileInfo(_fileName);
            QDir folder = fileInfo.absoluteDir();
            folder.cd(fileInfo.baseName());

            SetupAndRunTask(_splitter, folder);
        }
        else if (ui->MergeRadioButton->isChecked())
        {
            ui->RunButton->setEnabled(false);
            _merger = new TextureMerger();

            QFileInfo fileInfo(_fileName);
            QDir folder = fileInfo.absoluteDir();
            folder.cd(fileInfo.baseName());

            SetupAndRunTask(_merger, folder);
        }
    }

    void PackManagerMainWindow::OnThreadProcessingFinished()
    {
        _thread->exit();
        ui->RunButton->setEnabled(true);
    }

    void PackManagerMainWindow::OnSendMessage(QString message)
    {
        ui->MessageLabel->setText(message);
    }
}
