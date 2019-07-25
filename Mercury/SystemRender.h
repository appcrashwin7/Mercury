#pragma once

#include <qwidget.h>
#include <qpainter.h>

#include <PlanetarySystem.h>


class SystemRender : public QWidget
{
	Q_OBJECT;

	const PlanetarySystem * systemToDraw = nullptr;
	const QDateTime * currentTime = nullptr;


	static constexpr int MaxScaleInc = 12;
	static constexpr std::array<double, MaxScaleInc> Scales = {
		1.0e9, 5.0e9, 1.0e10, 5.0e10, 1.0e11, 5.0e11,
		1.0e12, 5.0e12, 1.0e13, 5.0e13, 1.0e14, 5.0e14
	};
	static constexpr int bodyDrawSize = 5;
	int currentScale = 0;

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
		auto scale = Scales[currentScale];

		if (systemToDraw != nullptr && currentTime != nullptr)
		{
			QPoint center(this->geometry().width() / 2, this->geometry().height() / 2);
			painter.setPen(QColor(0, 255, 0));

			std::vector<std::pair<QPoint, size_t>> points;
			points.emplace_back(std::make_pair(center, 0));


			auto drawBody = [&](const QPoint & pos, CelestialBody * body)
			{
				painter.setBrush(Qt::BrushStyle::SolidPattern);
				painter.drawEllipse(pos, bodyDrawSize, bodyDrawSize);
				painter.drawText(pos + QPoint(10, 0), body->getName());
			};


			for (size_t i = 0; i < systemToDraw->Bodies.size(); i++)
			{
				auto currentBody = systemToDraw->Bodies[i].get();

				if (i == 0)
				{
					drawBody(points.back().first, currentBody);
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
						auto ellipseCenter = coordsRes->first.operator-=(QPoint(c / scale, 0));
						auto rx = ((currentBody->orbit.majorAxis.value() / 2.0) / scale);
						auto ry = ((currentBody->orbit.minorAxis.value() / 2.0) / scale);

						painter.setBrush(Qt::BrushStyle::NoBrush);
						painter.drawEllipse(ellipseCenter, static_cast<int>(rx), static_cast<int>(ry));

						auto coords = Calc::getCoordsOfBody(rx, ry,
							currentBody->orbit.getMeanAnomaly(*currentTime).value()) + ellipseCenter;
						points.emplace_back(std::make_pair(coords, i));
						drawBody(coords, currentBody);
					}
				}
				
			}
		}
	}
	void wheelEvent(QWheelEvent * event)
	{
		auto change = event->angleDelta() / 8;
		if (!change.isNull())
		{
			if (change.y() > 0)
			{
				--currentScale;
			}
			else if(change.y() < 0)
			{
				++currentScale;
			}
		}
		
		if (currentScale < 0)
		{
			currentScale = 0;
		}
		if (currentScale > (MaxScaleInc - 1))
		{
			currentScale = (MaxScaleInc - 1);
		}

		event->accept();
		this->update();
	}
};