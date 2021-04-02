#pragma once

#include "SFML/Graphics.hpp"

namespace RTB
{
	class OrientedHitbox
	{
	public:
		/// Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
		OrientedHitbox(const sf::RectangleShape& Object, const int width, const int height);

		sf::Vector2f Points[4];

		/// Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
		void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max); 
	};
}