#pragma once

#include <qwidget.h>
#include <qpainter.h>

#include <PlanetarySystem.h>


class SystemRender : public QWidget
{
	Q_OBJECT;

	const PlanetarySystem * systemToDraw;

public:
	SystemRender()
		:QWidget(nullptr)
	{
		this->setObjectName("SystemRender");
	}
	~SystemRender() = default;

	void setNewSystem(const PlanetarySystem * newSystem)
	{
		systemToDraw = newSystem;
	}

	void paintEvent(QPaintEvent * event)
	{
		Q_UNUSED(event);
		QPainter painter(this);
		painter.fillRect(QRect(QPoint(0, 0), QSize(9999, 9999)), Qt::GlobalColor::darkBlue);

		if (systemToDraw != nullptr)
		{

		}
	}
};