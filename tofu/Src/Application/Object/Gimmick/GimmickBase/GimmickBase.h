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
	void Update()       override { UpdateMatrix(); }
	void PostUpdate()   override {}
	void DrawLit()      override {}

	// 座標確定処理
	virtual void UpdateMatrix()
	{
		m_mWorld = Math::Matrix::CreateTranslation(m_pos);
	}

	//========== ギミックの大分類 ==========
	enum class GimmickType
	{
		None,    // 未設定
		Vessel,  // 器（鍋など）
		Liquid,  // 液体（水・油など）
		Tool,    // 道具（まな板など）
	};
};