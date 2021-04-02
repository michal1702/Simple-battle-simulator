#include "OrientedHitbox.h"
#pragma once

namespace RTB
{
	OrientedHitbox::OrientedHitbox(const sf::RectangleShape& Object, const int width, const int height)
	{
		sf::Transform trans = Object.getTransform();
		Points[0] = trans.transformPoint(0.f, 0.f);
		Points[1] = trans.transformPoint(static_cast<float>(width), 0.f);
		Points[2] = trans.transformPoint(static_cast<float>(width), static_cast<float>(height));
		Points[3] = trans.transformPoint(0.f, static_cast<float>(height));
	}

	void OrientedHitbox::ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max)
	{
		Min = (Points[0].x * Axis.x + Points[0].y * Axis.y);
		Max = Min;
		for (int j = 1; j < 4; j++)
		{
			float Projection = (Points[j].x * Axis.x + Points[j].y * Axis.y);

			if (Projection < Min)
				Min = Projection;
			if (Projection > Max)
				Max = Projection;
		}
	}
}