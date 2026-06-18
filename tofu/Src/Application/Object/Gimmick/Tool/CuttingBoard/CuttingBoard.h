//CuttingBoard.h
#pragma once
#include "../ToolBase/ToolBase.h"

class C_CuttingBoard : public C_ToolBase
{
public:
	C_CuttingBoard() {}
	~C_CuttingBoard() {}

	void Init()     override;
	void DrawLit()  override;
};