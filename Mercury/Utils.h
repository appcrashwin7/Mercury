#pragma once

#include <vector>
#include <array>
#include <qtablewidget.h>

inline void fillNewRow(QTableWidget * tb, const std::vector<QString> & dt)
{
	tb->insertRow(tb->rowCount());
	int32_t col = 0;
	for (auto & i : dt)
	{
		tb->setItem(tb->rowCount() - 1, col, new QTableWidgetItem(i));
		++col;
	}
}
template<size_t size>
inline void fillNewRow(QTableWidget * tb, const std::array<QString, size> & dt)
{
	tb->insertRow(tb->rowCount());
	int32_t col = 0;
	for(auto & i : dt)
	{
		tb->setItem(tb->rowCount() - 1, col, new QTableWidgetItem(i));
		++col;
	}
}