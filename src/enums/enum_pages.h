#pragma once

#include <QObject>

class Pages : public QObject{
    Q_OBJECT

    public:
        enum EnPages
        {
            IGNORE = -1,
            LOGIN,
            SETTINGS,
            MAIN
        };
        Q_ENUMS(EnPages)
};
