//ResultScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

class C_ResultScene :public C_BaseScene
{
public:

	C_ResultScene();
	~C_ResultScene();

private:

	void Event()override;
	void Init()override;
};