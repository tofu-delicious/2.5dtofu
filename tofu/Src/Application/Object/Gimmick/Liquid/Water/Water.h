//Water.h
#pragma once
#include "../LiquidBase/LiquidBase.h"

class C_Water:public C_LiquidBase
{
public:
	
	C_Water(){}
	~C_Water(){}

	void Init()override;
	void DrawLit()override;
	
	//水状態を返す
	LiquidType GetLiquidType() const override
	{
		return LiquidType::Water;
	}
};