#pragma once

#include "Character.h"

namespace RTB
{
	sf::Vector2i Character::_isoTo2D(sf::Vector2f position)
	{
		return sf::Vector2i(static_cast<int>(((2 * position.y + position.x) / 2) / 25), static_cast<int>(((2 * position.y - position.x) / 2) / 25));
	}
	void Character::setPosition(sf::Vector2f position)
	{
		_movement->setSpritePosition(position);
	}

	void Character::render(sf::RenderWindow& window)
	{
		window.draw(_movement->getSprite());
		//_hitbox->render(window);
		_hp_bar->render(window);
	}

	bool Character::isAlive()
	{
		return _is_alive;
	}

	sf::Vector2f Character::getPosition()
	{
		return _movement->getSprite().getPosition();
	}

	bool Character::checkOrientedCollision(const sf::RectangleShape& Object1, const sf::RectangleShape& Object2)
	{
		OrientedHitbox OH1(Object1, static_cast<int>(Object1.getSize().x), static_cast<int>(Object1.getSize().y));
		OrientedHitbox OH2(Object2, static_cast<int>(Object2.getSize().x), static_cast<int>(Object2.getSize().y));

		// Create the four distinct axes that are perpendicular to the edges of the two rectangles
		sf::Vector2f Axes[4] = {
			sf::Vector2f(OH1.Points[1].x - OH1.Points[0].x,
			OH1.Points[1].y - OH1.Points[0].y),
			sf::Vector2f(OH1.Points[1].x - OH1.Points[2].x,
			OH1.Points[1].y - OH1.Points[2].y),
			sf::Vector2f(OH2.Points[0].x - OH2.Points[3].x,
			OH2.Points[0].y - OH2.Points[3].y),
			sf::Vector2f(OH2.Points[0].x - OH2.Points[1].x,
			OH2.Points[0].y - OH2.Points[1].y)
		};

		for (int i = 0; i < 4; i++) // For each axis...
		{
			float MinOH1, MaxOH1, MinOH2, MaxOH2;

			// ... project the points of both OBBs onto the axis ...
			OH1.ProjectOntoAxis(Axes[i], MinOH1, MaxOH1);
			OH2.ProjectOntoAxis(Axes[i], MinOH2, MaxOH2);

			// ... and check whether the outermost projected points of both OBBs overlap.
			// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
			if (!((MinOH2 <= MaxOH1) && (MaxOH2 >= MinOH1)))
				return false;
		}
		return true;
	}

	void Character::subtractHP(short value)
	{
		_health_points -= value;
		_hp_bar->shortenBar(value);
		if (_health_points < 1)
		{
			_movement->triggerDeath();
		}
	}

	sf::RectangleShape Character::getHitbox()
	{
		return _hitbox->getRectangle();
	}

	void Character::deadBody(sf::RenderWindow& window)
	{
		_movement->dead();
		window.draw(_movement->getSprite());
	}
}