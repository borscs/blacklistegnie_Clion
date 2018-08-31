#pragma once

#include "engine.h"

#include <QString>

class Handler
{
public:
    Handler();

    void scan(QString path);
    void lookup(QString hash);
    void generate(QString path);
    bool scanFolder(QString path);

private:
    Engine engine;
};


