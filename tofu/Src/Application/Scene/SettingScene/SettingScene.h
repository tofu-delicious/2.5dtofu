//SettingScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

class C_SettingScene :public C_BaseScene
{
public:
	C_SettingScene();
	~C_SettingScene();

private:

	void Event()override;
	void Init()override;

};