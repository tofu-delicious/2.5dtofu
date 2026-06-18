//Obstacle.h
#pragma once
#include "../ToolBase/ToolBase.h"

class C_Obstacle : public C_ToolBase
{
public:
	C_Obstacle() {}
	~C_Obstacle() {}

	void Init()     override;
	void DrawLit()  override;
};