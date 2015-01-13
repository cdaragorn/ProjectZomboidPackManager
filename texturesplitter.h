#ifndef TEXTURESPLITTER_H
#define TEXTURESPLITTER_H

#include "packfilemetadata.h"
#include "threadabletask.h"

#include <QObject>
#include <QDir>

namespace ProjectZomboidPackManager
{
    class TextureSplitter : public ThreadableTask
    {
        Q_OBJECT
    public:
        explicit TextureSplitter(QObject *parent = 0);
        ~TextureSplitter();

    protected:
        void DoTask();

    signals:

    public slots:
    };
}

#endif // TEXTURESPLITTER_H
