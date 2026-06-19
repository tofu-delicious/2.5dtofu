//GimmickFactory.cpp
#include "GimmickFactory.h"

// コンロありキッチンに置くギミックのパターン定義
// インデックスは「コンロありキッチンの何番目か」だけで進む
// → コンロなしキッチンでは OnKitchenSpawned() が早期リターンするため
//   このインデックスは絶対にズレない
const std::vector<std::vector<C_GimmickFactory::GimmickPlacement>>
C_GimmickFactory::PATTERN =
{
	// パターン0：ギミックなし（コンロありでも何も置かないケース）
	//{},

	// パターン1：鍋 + 油 + まな板
	{
		{ C_GimmickBase::GimmickType::Vessel, Pot,          -0.95f, 0.7f, -0.15f },
		{ C_GimmickBase::GimmickType::Liquid, Oil,          -0.95f, 0.82f, -0.15f},
		//{ C_GimmickBase::GimmickType::Tool,   CuttingBoard,  0.4f,   0.0f,  0.0f  },
	},

	// パターン2：鍋 + 水
	{
		{ C_GimmickBase::GimmickType::Vessel, Pot,          -0.75f, -0.1f, -0.02f },
		{ C_GimmickBase::GimmickType::Liquid, Water,        -0.75f,  0.0f, -0.02f },
	},

	// パターン3：まな板のみ
	{
		{ C_GimmickBase::GimmickType::Tool,   CuttingBoard,  0.0f,   0.0f,  0.0f  },
	},
};

std::vector<std::shared_ptr<C_GimmickBase>>
C_GimmickFactory::GetNextPattern(float a_kitchenBaseX, float a_scrollSpeed)
{
	std::vector<std::shared_ptr<C_GimmickBase>> result;

	const auto& placements = PATTERN[m_currentIndex];

	for (const auto& p : placements)
	{
		std::shared_ptr<C_GimmickBase> gimmick;

		// 大分類 → 小分類の順で実体を生成
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
			gimmick = std::make_shared<C_CuttingBoard>();
			break;

		default:
			continue; // 知らない種類はスキップ
		}

		// 初期化 → 座標設定 → 行列更新
		gimmick->Init();
		gimmick->SetPos({ a_kitchenBaseX + p.offsetX, p.offsetY, p.offsetZ });
		gimmick->UpdateMatrix();

		result.push_back(gimmick);
	}

	// インデックスを1進める（末尾まで来たら0に戻す）
	m_currentIndex = (m_currentIndex + 1) % static_cast<int>(PATTERN.size());

	return result;
}