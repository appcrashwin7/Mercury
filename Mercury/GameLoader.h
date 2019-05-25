#pragma once

#include "MercurySave.h"

class GameLoader : public MercurySave
{

public:
	GameLoader() = delete;
	GameLoader(const QString & fileName)
		:MercurySave(fileName)
	{
	}
	~GameLoader() = default;
};