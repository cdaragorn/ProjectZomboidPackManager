#ifndef TEXTUREUNPACKER_H
#define TEXTUREUNPACKER_H

#include "threadabletask.h"

#include <QObject>

namespace ProjectZomboidPackManager
{
    class TextureUnpacker : public ThreadableTask
    {
        Q_OBJECT
    public:
        explicit TextureUnpacker(QObject *parent = 0);
        ~TextureUnpacker();

    protected:
        void DoTask();

    signals:

    public slots:
    };
}

#endif // TEXTUREUNPACKER_H
