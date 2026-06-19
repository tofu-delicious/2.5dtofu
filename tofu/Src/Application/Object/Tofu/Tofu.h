//Tofu.h
#pragma once
#include "../ObjectBase/ObjectBase.h"
#include "../Gimmick/GimmickBase/GimmickBase.h"
#include "../Gimmick/Liquid/LiquidBase/LiquidBase.h"

class C_Tofu:public C_ObjectBase
{
public:

	//とうふ自身の形態定義
	enum class FormType
	{
		Normal,	//通常とうふ
		Oil,	//揚げとうふ
	};

	C_Tofu(){}
	~C_Tofu()override{}

	void Init()			override;
	void PreUpdate()	override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//とうふの操作処理（ジャンプ）
	void JumpTofu();

	//行列処理
	void UpdateMatrix();

	//レイ判定
	void CheckRay();

	//球判定
	void CheckSphere();

	//衝突判定後の処理
	void OnHit()override{}

	//ギミック衝突後の分岐処理
	void OnHitGimmick(C_GimmickBase* a_gimmick);

	//消滅処理（アニメ再生 ⇒ 消滅フラグ）
	void StartDeathAnim();

	//デバッグ処理
	void ImGui()override;

	//============= ゲッター ===============
	
private:

	//=============== 定数 =================
	static constexpr Math::Vector3 INITIAL_POS = { -0.5f,1.0f,-0.1f };
	static constexpr float MIN_RAY_RANGE = 0.15f;						//RAYの最低保証
	static constexpr float JUMP_POW_Y = 0.04f;							//Y軸方向のジャンプ力
	static constexpr float GRAVITY_INCREMENT = 0.003f;				//重力減算値

	//============ 状態フラグ ==============
	bool m_isSpaceKey = false;		//キー制御
	bool m_isJumping = false;		//true：ジャンプした　false：ジャンプしていない
	bool m_isDebugOpen = false;		//true：デバッグウィンドウが開いている　false：開いていない

	//============= 動的変数 ===============
	FormType m_currentForm = FormType::Normal;

	float m_gravity = 0.0f;			//重力（ジャンプ処理）
};