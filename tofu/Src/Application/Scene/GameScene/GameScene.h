#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class C_Tofu;
class C_Kitchen;

class GameScene : public C_BaseScene
{
public :

	GameScene();
	~GameScene();

	

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<C_Tofu> m_tofu = nullptr;
	std::shared_ptr<C_Kitchen> m_kitchen = nullptr;
};
