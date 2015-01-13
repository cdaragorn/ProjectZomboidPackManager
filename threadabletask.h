#ifndef THREADABLETASK_H
#define THREADABLETASK_H

#include "packfilemetadata.h"

#include <QDir>
#include <QObject>

namespace ProjectZomboidPackManager
{
    class ThreadableTask : public QObject
    {
        Q_OBJECT
    public:
        explicit ThreadableTask(QObject *parent = 0);
        ~ThreadableTask();

        void Prepare(QDir folder, PackFileMetaData& fileData);

    protected:
        QDir _folder;
        PackFileMetaData* _fileData;

        virtual void DoTask() = 0;

    signals:
        void SendMessage(QString message);
        void FinishedTask();

    public slots:
        void Run();
    };
}

#endif // THREADABLETASK_H
