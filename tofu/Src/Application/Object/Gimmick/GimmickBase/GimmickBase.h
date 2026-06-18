//GimmickBase.h
#pragma once
#include "../../ObjectBase/ObjectBase.h"

class C_GimmickBase : public C_ObjectBase
{
public:
	C_GimmickBase() {}
	virtual ~C_GimmickBase() {}

	void Init()         override {}
	void PreUpdate()    override {}
	void Update()       override;
	void PostUpdate()   override {}
	void DrawLit()      override {}

	// スクロール速度をKitchenManagerから受け取る
	void SetScrollSpeed(float a_speed) { m_scrollSpeed = a_speed; }

	// ギミックの大分類（プレイヤー側の当たり判定処理で使う）
	enum class GimmickType
	{
		None,       // 未定義
		Liquid,     // 液体（水・油）→ 形態変化
		Vessel,     // 器（鍋など）  → 縁でダメージ
		Tool,       // 道具          → ぶつかるだけ・ダメージ
	};

	// 自分の種類を返す（純粋仮想）
	virtual GimmickType GetGimmickType() const = 0;

protected:
	float m_scrollSpeed = 0.0f;
};