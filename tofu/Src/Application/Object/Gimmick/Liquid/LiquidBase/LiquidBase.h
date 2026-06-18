//LiquidBase.h ============= 液体の基底クラス =============
#pragma once
#include "../../GimmickBase/GimmickBase.h"

class C_LiquidBase : public C_GimmickBase
{
public:
	C_LiquidBase() {}
	virtual ~C_LiquidBase() {}

	// 大分類：液体
	GimmickType GetGimmickType() const override
	{
		return GimmickType::Liquid;
	}

	// 何形態に変化するか（Water・Oilで異なる）
	enum class FormType
	{
		Water,  // 水形態
		Oil,    // 油形態
	};

	virtual FormType GetFormType() const = 0;
};