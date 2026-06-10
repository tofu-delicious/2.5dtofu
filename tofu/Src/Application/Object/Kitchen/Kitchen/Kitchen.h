//Kitchen.h
#pragma once
#include "../../ObjectBase/ObjectBase.h"

class C_Kitchen:public C_ObjectBase
{
public:

	//キッチンの種類
	enum class KitchenType
	{
		withAppliances,		//コンロ・シンクあり
		withoutAppliances,	//コンロ・シンクなし
	};

	C_Kitchen(){}
	C_Kitchen(KitchenType type):m_kitchenType(type){}
	~C_Kitchen(){}

	void Init()			override;
	void PreUpdate()	override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//行列処理
	void UpdateMatrix();

	//デバッグ処理
	void ImGui()	override;

private:

	//================= 定数 ===================
	static constexpr Math::Vector3 INITIAL_POS = { 0.0f,0.0f,0.0f };

	//============== 状態フラグ ================

	//=============== 動的変数　================
	KitchenType m_kitchenType = KitchenType::withAppliances;	//キッチンの種類（デフォルトはコンロシンクあり）
};