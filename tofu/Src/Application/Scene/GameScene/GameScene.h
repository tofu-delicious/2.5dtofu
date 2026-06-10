#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class C_Tofu;
class C_KitchenManager;

class GameScene : public C_BaseScene
{
public :

	GameScene();
	~GameScene();

	//「m_kitchens」の内容を「m_objList」へ格納
	void SyncKitchensObjList();

	//ImGuiManagerへインスタンス情報を送る関数
	void SetUpImGuiManager();

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<C_Tofu> m_tofu = nullptr;
	std::shared_ptr<C_KitchenManager> m_kitchenMgr = nullptr;
};
