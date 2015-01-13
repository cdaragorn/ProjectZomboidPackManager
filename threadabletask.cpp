#include "threadabletask.h"

namespace ProjectZomboidPackManager
{


    ThreadableTask::ThreadableTask(QObject *parent)
        : QObject(parent),
          _fileData(nullptr)
    {

    }

    ThreadableTask::~ThreadableTask()
    {

    }

    void ThreadableTask::Prepare(
            QDir folder,
            PackFileMetaData& fileData)
    {
        _folder = folder;
        _fileData = &fileData;
    }

    void ThreadableTask::Run()
    {
        DoTask();
        emit FinishedTask();
    }

}
