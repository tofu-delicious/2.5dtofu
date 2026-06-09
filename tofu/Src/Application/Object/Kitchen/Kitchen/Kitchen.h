//Kitchen.h
#pragma once
#include "../../ObjectBase/ObjectBase.h"

class C_Kitchen:public C_ObjectBase
{
public:
	C_Kitchen(){}
	~C_Kitchen(){}

	void Init()			override;
	void PreUpdate()	override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//行列処理
	void UpdateMatrix();

	//当たり判定（キッチンが地面の役割と同義）
	void InitCollision();

	//デバッグ処理
	void ImGui()	override;

private:

	//================= 定数 ===================
	static constexpr Math::Vector3 INITIAL_POS = { 0.0f,0.0f,0.0f };

	//============== 状態フラグ ================
	bool m_isDebugOpen = false;;

	//=============== 動的変数　================

};