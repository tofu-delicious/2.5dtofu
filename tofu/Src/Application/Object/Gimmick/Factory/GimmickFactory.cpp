// GimmickFactory.cpp
#include "GimmickFactory.h"

const std::vector<std::vector<C_GimmickFactory::GimmickPlacement>>
C_GimmickFactory::PATTERN =
{
	// パターン0：ギミックなし
	{},

	// パターン1：鍋（器）+ 油（液体）+ 障害物
	{
		{ C_GimmickBase::GimmickType::Vessel, Pot,      0.0f, 0.0f, 0.0f },
		{ C_GimmickBase::GimmickType::Liquid, Oil,      0.0f, 0.1f, 0.0f },
		{ C_GimmickBase::GimmickType::Tool,   Obstacle, 1.2f, 0.0f, 0.0f },
	},

	// パターン2：鍋（器）+ 水（液体）
	{
		{ C_GimmickBase::GimmickType::Vessel, Pot,   0.4f, 0.0f, 0.0f },
		{ C_GimmickBase::GimmickType::Liquid, Water, 0.4f, 0.1f, 0.0f },
	},

	// パターン3：障害物のみ
	{
		{ C_GimmickBase::GimmickType::Tool, Obstacle, 0.8f, 0.0f, 0.0f },
	},
};

std::vector<std::shared_ptr<C_GimmickBase>>
C_GimmickFactory::GetNextPattern(float kitchenBaseX, float scrollSpeed)
{
	std::vector<std::shared_ptr<C_GimmickBase>> result;

	const auto& placements = PATTERN[m_currentIndex];

	for (const auto& p : placements)
	{
		std::shared_ptr<C_GimmickBase> gimmick;

		switch (p.type)
		{
		case C_GimmickBase::GimmickType::Liquid:
			if (p.subType == Water) gimmick = std::make_shared<C_Water>();
			else                    gimmick = std::make_shared<C_Oil>();
			break;

		case C_GimmickBase::GimmickType::Vessel:
			gimmick = std::make_shared<C_Pot>();
			break;

		case C_GimmickBase::GimmickType::Tool:
			gimmick = std::make_shared<C_Obstacle>();
			break;

		default:
			continue;
		}

		gimmick->Init();
		gimmick->SetScrollSpeed(scrollSpeed);
		gimmick->SetPos({ kitchenBaseX + p.offsetX, p.offsetY, p.offsetZ });
		result.push_back(gimmick);
	}

	m_currentIndex = (m_currentIndex + 1) % PATTERN.size();
	return result;
}