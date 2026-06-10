//KitchenFactory.cpp
#include "KitchenFactory.h"

C_KitchenFactory::C_KitchenFactory(){}

C_KitchenFactory::~C_KitchenFactory(){}

//出現順番（コンロ等なし ⇒ コンロ等なし ⇒ コンロ等あり）
const std::vector<C_Kitchen::KitchenType> C_KitchenFactory::PATTERN =
{
	C_Kitchen::KitchenType::withoutAppliances,
	C_Kitchen::KitchenType::withoutAppliances,
	C_Kitchen::KitchenType::withAppliances,
};

//次のキッチン情報を取得
std::shared_ptr<C_Kitchen> C_KitchenFactory::GetNext()
{
	//現在のインデックスの種類でキッチンを生成
	auto kitchen = std::make_shared<C_Kitchen>(PATTERN[m_currentIndex]);
	//キッチン初期化処理
	kitchen->Init();
	//インデックスを循環
	m_currentIndex = (m_currentIndex + 1) % PATTERN.size();
	//新たに生成したキッチンを返却
	return kitchen;
}
