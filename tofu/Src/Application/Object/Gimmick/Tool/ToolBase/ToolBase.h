//ToolBase.h
#pragma once
#include "../../GimmickBase/GimmickBase.h"

class C_ToolBase : public C_GimmickBase
{
public:
	C_ToolBase() {}
	virtual ~C_ToolBase() {}

	// 大分類：道具
	GimmickType GetGimmickType() const override
	{
		return GimmickType::Tool;
	}

protected:
	std::shared_ptr<KdModelData> m_model;
};