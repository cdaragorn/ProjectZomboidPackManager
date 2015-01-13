#ifndef TEXTUREMERGER_H
#define TEXTUREMERGER_H

#include "packfilemetadata.h"
#include "threadabletask.h"

#include <QObject>
#include <QDir>

namespace ProjectZomboidPackManager
{
    class TextureMerger : public ThreadableTask
    {
        Q_OBJECT
    public:
        explicit TextureMerger(QObject *parent = 0);
        ~TextureMerger();

    protected:
        void DoTask();

    signals:

    public slots:
    };
}

#endif // TEXTUREMERGER_H
