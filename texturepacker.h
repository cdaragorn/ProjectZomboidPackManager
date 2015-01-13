#ifndef TEXTUREPACKER_H
#define TEXTUREPACKER_H

#include "packfilemetadata.h"
#include "threadabletask.h"

#include <QDir>
#include <QObject>

namespace ProjectZomboidPackManager
{
    class TexturePacker : public ThreadableTask
    {
        Q_OBJECT
    public:
        explicit TexturePacker(QObject *parent = 0);
        ~TexturePacker();

    protected:
        void DoTask();

    signals:

    public slots:
    };
}

#endif // TEXTUREPACKER_H
