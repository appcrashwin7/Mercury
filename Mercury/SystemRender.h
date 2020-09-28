#pragma once

#include <qwidget.h>
#include <qpainter.h>

#include <PlanetarySystem.h>


class SystemRender : public QWidget
{
	Q_OBJECT;

	static constexpr int bodyDrawSize = 5;
	static constexpr double baseScale = 1.0e6;
	static constexpr double scaleInc = 2;

	const PlanetarySystem * systemToDraw = nullptr;
	const QDateTime * currentTime = nullptr;

	int scaleMult = 0;
	size_t firstBody = 0;

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
		auto scale = baseScale;
		if (scaleMult > 0)
		{
			scale *= (std::pow(scaleMult, scaleInc));
		}

		if (systemToDraw != nullptr && currentTime != nullptr)
		{
			painter.setPen(QColor(0, 255, 0));
			std::vector<std::pair<QPoint, size_t>> points;
			
			painter.drawText(QPoint(0, 15), QString::number(scale));

			auto drawBody = [&](const QPoint & pos, CelestialBody * body)
			{
				painter.setBrush(Qt::BrushStyle::SolidPattern);
				painter.drawEllipse(pos, bodyDrawSize, bodyDrawSize);
				painter.drawText(pos + QPoint(10, 0), body->getName());
			};

			for (size_t i = firstBody; i < systemToDraw->Bodies.size(); i++)
			{
				auto currentBody = systemToDraw->Bodies[i].get();

				if (i == firstBody)
				{
					QPoint center(this->geometry().width() / 2, this->geometry().height() / 2);
					points.emplace_back(std::make_pair(center, firstBody));
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

					if (coordsRes != points.end() && currentBody->orbit.majorAxis.value() > (10 * scale))
					{
						auto ellipseCenter = coordsRes->first;
						auto c = 0.0;
						auto coords = QPoint();

						painter.setBrush(Qt::BrushStyle::NoBrush);
						auto mAn = currentBody->orbit.getMeanAnomaly(*currentTime).value();

						if (!currentBody->orbit.isCircular)
						{
							c = currentBody->orbit.majorAxis.value() * currentBody->orbit.eccentricity;
							ellipseCenter = ellipseCenter - QPoint(c / scale, 0);
						}

						auto rx = ((currentBody->orbit.majorAxis.value() / 2.0) / scale);
						auto ry = (((currentBody->orbit.majorAxis.value() * (1.0 - currentBody->orbit.eccentricity)) / 2.0) / scale);
						painter.drawEllipse(ellipseCenter, static_cast<int>(rx), static_cast<int>(ry));
						coords = Calc::getCoordsOfBody(rx, ry, mAn) + ellipseCenter;

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
				--scaleMult;
			}
			else if(change.y() < 0)
			{
				++scaleMult;
			}
		}
		
		if (scaleMult < 0)
		{
			scaleMult = 0;
		}

		event->accept();
		this->update();
	}


public slots:
	void changeFirstBody(QTreeWidgetItem * item, int column)
	{
		if (item != nullptr)
		{
			if (!(systemToDraw == nullptr || currentTime == nullptr))
			{
				auto newBody = 0;
				auto res = std::find_if(systemToDraw->Bodies.begin(), systemToDraw->Bodies.end(), 
					[&newBody, item, column](const CelestialBodyPtr & current)
				{
					if (current->getName() == item->text(column))
					{
						return true;
					}
					++newBody;
					return false;
				});

				if (res != systemToDraw->Bodies.end())
				{
					firstBody = newBody;
					if (firstBody == static_cast<size_t>(-1) ||
						firstBody >= systemToDraw->Bodies.size())
					{
						firstBody = 0;
					}
					this->update();
					scaleMult = 0;
				}
			}
		}
	}
};