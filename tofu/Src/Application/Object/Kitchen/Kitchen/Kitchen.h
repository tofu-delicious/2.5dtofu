//Kitchen.h
#pragma once
#include "../../ObjectBase/ObjectBase.h"

class C_Kitchen:public C_ObjectBase
{
public:

	//キッチンの種類
	enum class KitchenType
	{
		None,				//初期化用
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

	//キッチンタイプ取得
	KitchenType GetKitchenType() const { return m_kitchenType; }

private:

	//================= 定数 ===================

	//============== 状態フラグ ================

	//=============== 動的変数　================
	KitchenType m_kitchenType = KitchenType::None;	//キッチンの種類（デフォルトはコンロシンクあり）
};