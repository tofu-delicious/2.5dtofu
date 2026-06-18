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

	// 液体の種類（何がトリガーになるか）
	enum class LiquidType
	{
		Water,  // 水形態：油状態を解除する
		Oil,    // 油形態：揚げ豆腐形態にする
	};

	virtual LiquidType GetLiquidType() const = 0;
};