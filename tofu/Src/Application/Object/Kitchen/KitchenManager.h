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
	static constexpr Math::Vector3 INITIAL_POS = Math::Vector3{ 0.0f,-0.2f,0.0f };	//キッチンの初期座標
	static constexpr float KITCHEN_WIDTH = 2.4f;		//キッチンの横幅：2.41m

	static constexpr float SCROLL_SPEED = 0.01f;								//スクロール速度
	static constexpr float SPAWN_POS_X = 6.0f;									//キッチンを画面右端に出すX座標
	static constexpr float SPAWN_THRESHOLD = SPAWN_POS_X - KITCHEN_WIDTH;		//次のキッチンを出すX座標のしきい値2
	static constexpr float DESTROY_THRESHOLD = -3.0f;							//キッチンを消すX座標のしきい値
	

	

	//============ 状態フラグ ===============
	bool m_isDebugOpen = false;

	//============== 動的変数 ===============
	//float SCROLL_SPEED = 0.05f;			//スクロール速度
	//float SPAWN_THRESHOLD = 5.0f;		//次のキッチンを出すX座標のしきい値
	//float DESTROY_THRESHOLD = -20.0f;	//キッチンを消すX座標のしきい値
	//float SPAWN_POS_X = 15.0f;			//キッチンを画面右端に出すX座標
};