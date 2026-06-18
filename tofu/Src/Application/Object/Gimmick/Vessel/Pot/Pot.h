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
	void ImGui()	override;
};