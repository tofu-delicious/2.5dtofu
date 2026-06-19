//Pot.h
#pragma once
#include "../VesselBase/VesselBase.h"

class C_Pot : public C_VesselBase
{
public:
	C_Pot() {}
	~C_Pot() {}

	void Init()     override;
	void DrawLit()  override;

private:

	//============ 定数 ==============
	static constexpr Math::Vector3 INITIAL_POS = { 0.0f,0.7f,0.2f};
};