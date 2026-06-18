#pragma once

#include"../BaseScene/BaseScene.h"

//前方宣言
class C_BackGroundScroller;	//背景スクロール
class C_Tofu;				//とうふ
class C_KitchenManager;		//キッチン
class C_GimmickBase;		//ギミック基底クラス

class GameScene : public C_BaseScene
{
public :

	GameScene();
	~GameScene();

	//「m_kitchens」の内容を「m_objList」へ格納
	void SyncKitchensObjList();

	//「m_gimmicks」の内容を「m_objList」へ格納
	void SyncGimmicksObjList();

	//ImGuiManagerへインスタンス情報を送る関数
	void SetUpImGuiManager();

private:

	void Event() override;
	void Init()  override;

	//=============== インスタンス =============
	std::shared_ptr<C_BackGroundScroller> m_back = nullptr;
	std::shared_ptr<C_Tofu> m_tofu = nullptr;
	std::shared_ptr<C_KitchenManager> m_kitchenMgr = nullptr;

	//================= 動的変数 ===============
	static constexpr Math::Vector3 CAMERA_POS = { 0.0f,1.0f,-1.0f };
	static constexpr float CAMERA_ROTATE = 10.0f;
};
