//KitchenFactory.h
#pragma once
#include "../Kitchen/Kitchen.h"

class C_KitchenFactory
{
public:
	C_KitchenFactory();
	~C_KitchenFactory();

	//次のキッチンを取得
	std::shared_ptr<C_Kitchen> GetNext();

private:

	//循環パターン定義
	static const std::vector<C_Kitchen::KitchenType> PATTERN;

	//現在のインデックス
	int m_currentIndex = 0;

};