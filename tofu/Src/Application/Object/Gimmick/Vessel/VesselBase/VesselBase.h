//Vessel.h ============= 器の基底クラス ============
#pragma once
#include "../../GimmickBase/GimmickBase.h"

class C_VesselBase : public C_GimmickBase
{
public:
	C_VesselBase() {}
	virtual ~C_VesselBase() {}

	// 大分類：器
	GimmickType GetGimmickType() const override
	{
		return GimmickType::Vessel;
	}
};