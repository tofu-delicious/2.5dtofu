//Oil.h
#pragma once
#include "../LiquidBase/LiquidBase.h"

class C_Oil : public C_LiquidBase
{
public:
	C_Oil() {}
	~C_Oil() {}

	void Init()     override;
	void DrawLit()  override;

	// 油形態を返す
	LiquidType GetLiquidType() const override
	{
		return LiquidType::Oil;
	}
};