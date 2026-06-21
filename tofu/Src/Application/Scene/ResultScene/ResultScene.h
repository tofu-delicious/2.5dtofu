//ResultScene.h
#pragma once

#include "../BaseScene/BaseScene.h"

class C_UIBase;
class C_UIFade;

class C_ResultScene :public C_BaseScene
{
public:

	C_ResultScene();
	~C_ResultScene();

private:

	void Event()override;
	void Init()override;

	//============== 定数 ===============
	static constexpr Math::Vector3 BACKGROUND_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACKGROUND_RECT = { 0,0,1280,720 };
	static constexpr float BACKGROUND_ALPHA = 0.6f;

	static constexpr Math::Vector3 BACK_POS = { 0.0f,0.0f,0.0f };
	static constexpr Math::Rectangle BACK_RECT = { 0,0,850,500 };

	static constexpr Math::Vector3 RETRY_POS = { -200.0f,-170.0f,0.0f };
	static constexpr Math::Rectangle RETRY_RECT = { 0,64,192,64 };

	static constexpr Math::Vector3 TITLE_POS = { 200.0f,-170.0f,0.0f};
	static constexpr Math::Rectangle TITLE_RECT = { 0,128,192,64 };

	//========== インスタンス ============
	std::shared_ptr<C_UIBase> m_backGround = nullptr;	//薄い背景
	std::shared_ptr<C_UIBase> m_back = nullptr;			//背景
		//タイム表示
		//ランク
	std::shared_ptr<C_UIBase> m_retry = nullptr;		//リトライ
	std::shared_ptr<C_UIBase> m_title = nullptr;		//タイトル
};