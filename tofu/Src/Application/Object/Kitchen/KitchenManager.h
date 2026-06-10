//KitchenFactory.h
#pragma once
#include "../Kitchen/Factory/KitchenFactory.h"

class C_KitchenManager
{
public:
	C_KitchenManager(){}
	~C_KitchenManager(){}

	void Init();
	void Update();
	
	//objListに渡すため、外部から参照できるようにする
	const std::list<std::shared_ptr<C_Kitchen>>& GetKitchens() const
	{
		return m_kitchens;
	}

	//============= デバッグ ================
	void ImGui();

private:

	//===== インスタンス・可変長配列 ========
	//キッチンのリスト
	std::list<std::shared_ptr<C_Kitchen>> m_kitchens;

	//生成クラス
	C_KitchenFactory m_factory;

	//================ 定数 =================
	//static constexpr float SCROLL_SPEED = 0.05f;		//スクロール速度
	//static constexpr float SPAWN_THRESHOLD = 5.0f;		//次のキッチンを出すX座標のしきい値2
	//static constexpr float DESTROY_THRESHOLD = -20.0f;	//キッチンを消すX座標のしきい値
	//static constexpr float SPAWN_POS_X = 15.0f;			//キッチンを画面右端に出すX座標

	//============ 状態フラグ ===============
	bool m_isDebugOpen = false;

	//============== 動的変数 ===============
	float SCROLL_SPEED = 0.05f;			//スクロール速度
	float SPAWN_THRESHOLD = 5.0f;		//次のキッチンを出すX座標のしきい値
	float DESTROY_THRESHOLD = -20.0f;	//キッチンを消すX座標のしきい値
	float SPAWN_POS_X = 15.0f;			//キッチンを画面右端に出すX座標
};