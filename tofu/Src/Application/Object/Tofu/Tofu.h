//Tofu.h
#pragma once
#include "../ObjectBase/ObjectBase.h"

class C_Tofu:public C_ObjectBase
{
public:
	C_Tofu(){}
	~C_Tofu()override{}

	void Init()			override;
	void PreUpdate()	override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//とうふの操作処理（ジャンプ）
	void MoveTofu();

	//座標確定処理
	void CommitPos();

	//行列処理
	void UpdateMatrix();

	//レイ判定
	void CheckRay();

	//球判定
	void CheckSphere();

	//衝突判定後の処理
	void OnHit()override{}

	//デバッグ処理
	void ImGui()override;

	//============= ゲッター ===============
	

private:

	//=============== 定数 =================
	static constexpr float JUMP_POW = 0.15f;
	static constexpr float GRAVITY_INCREMENT = 0.001f;

	//============ 状態フラグ ==============
	bool m_isSpaceKey = false;
	bool m_isJumping = false;

	//============= 動的変数 ===============
	float m_moveSpeed = 0.0f;	//スピード
	float m_gravity = 0.0f;		//重力（ジャンプ処理）
};