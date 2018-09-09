#pragma once

#include "engine.h"
#include "utils.h"
#include "jsonhelper.h"

#include <QString>

class EngineHandler
{
public:
	EngineHandler();

	void scan(QString path);
	void lookup(QString hash);
	void generate(QString path);
	bool scanFolder(QString path);

private:
	Engine engine;
	JsonHelper jsonfu;
	utils::Utils utils;
};
