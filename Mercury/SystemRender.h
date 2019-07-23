#pragma once

#include <qwidget.h>
#include <qpainter.h>

#include <PlanetarySystem.h>


class SystemRender : public QWidget
{
	Q_OBJECT;

	const PlanetarySystem * systemToDraw = nullptr;
	const QDateTime * currentTime = nullptr;

	static constexpr double Scale = 1.0e10;

	static constexpr int minorDrawSize = 5;
	static constexpr int majorDrawSize = 10;

public:
	static QString getWidgetName()
	{
		return "SystemRender";
	}

	SystemRender()
		:QWidget(nullptr)
	{
		this->setObjectName(SystemRender::getWidgetName());
	}
	~SystemRender() = default;

	void setNewSystem(const PlanetarySystem * newSystem)
	{
		systemToDraw = newSystem;
	}
	void setTime(const QDateTime * timer)
	{
		currentTime = timer;
	}

	void paintEvent(QPaintEvent * event)
	{
		Q_UNUSED(event);
		QPainter painter(this);
		painter.fillRect(QRect(QPoint(0, 0), QSize(9999, 9999)), Qt::GlobalColor::darkBlue);

		if (systemToDraw != nullptr && currentTime != nullptr)
		{
			QPoint center(this->geometry().width() / 2, this->geometry().height() / 2);
			painter.setPen(QColor(0, 255, 0));

			std::vector<std::pair<QPoint, size_t>> points;
			points.emplace_back(std::make_pair(center, 0));


			for (size_t i = 0; i < systemToDraw->Bodies.size(); i++)
			{
				auto currentBody = systemToDraw->Bodies[i].get();

				if (i == 0)
				{
					painter.setBrush(Qt::BrushStyle::SolidPattern);
					painter.drawEllipse(points.back().first, majorDrawSize, majorDrawSize);
				}
				else
				{
					auto prevBodyID = currentBody->orbit.parent.value();

					auto coordsRes = std::find_if(points.begin(), points.end(), [prevBodyID](const std::pair<QPoint, size_t> & curr)
					{
						if (curr.second == prevBodyID)
						{
							return true;
						}
						return false;
					});

					if (coordsRes != points.end())
					{
						auto c = currentBody->orbit.majorAxis.value() * currentBody->orbit.eccentricity;
						auto ellipseCenter = coordsRes->first.operator-=(QPoint(c / Scale, 0));
						auto rx = ellipseCenter.x() + ((currentBody->orbit.majorAxis.value() / 2.0) / Scale);
						auto ry = ellipseCenter.y() + ((currentBody->orbit.minorAxis.value() / 2.0) / Scale);

						painter.setBrush(Qt::BrushStyle::NoBrush);
						painter.drawEllipse(ellipseCenter, static_cast<int>(rx), static_cast<int>(ry));

						painter.setBrush(Qt::BrushStyle::SolidPattern);

						auto coords = Calc::getCoordsOfBody(rx, ry,
							currentBody->orbit.getMeanAnomaly(*currentTime).value()) + ellipseCenter;
						painter.drawEllipse(coords, minorDrawSize, minorDrawSize);
						points.emplace_back(std::make_pair(coords, i));
					}
					break;
				}
				
			}
		}
	}
};