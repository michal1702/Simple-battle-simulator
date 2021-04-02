#pragma once

#include "RealTimeBattle.h"

namespace RTB
{
	void RealTimeBattle::_zoomEvent()
	{
		if (_event.mouseWheel.delta == -1)
		{
			if (_zoom * ZOOM_UP >= 0.8)
				return;
			else
			{
				_zoom *= ZOOM_UP;
				_camera.zoom(static_cast<float>(ZOOM_UP));
			}
		}
		else if (_event.mouseWheel.delta == 1)
		{
			if (_zoom * ZOOM_DOWN <= 0.5)
				return;
			else
			{
				_zoom *= ZOOM_DOWN;
				_camera.zoom(static_cast<float>(ZOOM_DOWN));
			}
		}
	}

	void RealTimeBattle::_armyCreation()
	{
		unsigned seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::mt19937 RNG(seed);
		std::uniform_real_distribution<float> enemy_position_height(12, 36);
		std::uniform_real_distribution<float> enemy_position_width(1, 5);
		sf::Vector2f position;

		for (unsigned short i = 0; i < 8; ++i)
			_list_of_enemies.emplace_back(new Swordsman(_asset_manager.getTexture("enemy_swordsman"), 100, _tile_map->getWalkableArea()));
		for (unsigned short i = 0; i < 8; ++i)
			_list_of_enemies.emplace_back(new Archer(_asset_manager.getTexture("enemy_archer"), 100, _asset_manager.getTexture("arrow"), _tile_map->getWalkableArea()));
		for (unsigned short i = 0; i < 8; ++i)
			_list_of_enemies.emplace_back(new Spearman(_asset_manager.getTexture("enemy_spearman"), 100, _tile_map->getWalkableArea()));
		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_enemies.begin(); iterator != _list_of_enemies.end(); iterator++)
		{
			position.x = enemy_position_height(RNG) * 25;
			position.y = enemy_position_width(RNG) * 25;
			position = _tile_map->_twoDToIso(position);
			(*iterator)->setPosition({ position.x,position.y });
			while (_checkPlacementCollisions(iterator))
			{
				position.x = enemy_position_height(RNG) * 25;
				position.y = enemy_position_width(RNG) * 25;
				position = _tile_map->_twoDToIso(position);
				(*iterator)->setPosition({ position.x,position.y });
			}
		}

		for (unsigned short i = 0; i < 7; ++i)
			_list_of_allies.emplace_back(new Swordsman(_asset_manager.getTexture("ally_swordsman"), 100, _tile_map->getWalkableArea()));
		for (unsigned short i = 0; i < 8; ++i)
			_list_of_allies.emplace_back(new Archer(_asset_manager.getTexture("ally_archer"), 100, _asset_manager.getTexture("arrow"), _tile_map->getWalkableArea()));
		for (unsigned short i = 0; i < 8; ++i)
			_list_of_allies.emplace_back(new Spearman(_asset_manager.getTexture("ally_spearman"), 100, _tile_map->getWalkableArea()));

		_list_of_allies.emplace_back(new Player(_asset_manager.getTexture("player"), 100, _asset_manager.getTexture("arrow")));
		_player = _list_of_allies.back();

		std::uniform_real_distribution<float> ally_position_height(12, 36);
		std::uniform_real_distribution<float> ally_position_width(59, 63);

		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_allies.begin(); iterator != _list_of_allies.end(); iterator++)
		{
			position.x = ally_position_height(RNG) * 25;
			position.y = ally_position_width(RNG) * 25;
			position = _tile_map->_twoDToIso(position);
			(*iterator)->setPosition({ position.x,position.y });
			while (_checkPlacementCollisions(iterator))
			{
				position.x = ally_position_height(RNG) * 25;
				position.y = ally_position_width(RNG) * 25;
				position = _tile_map->_twoDToIso(position);
				(*iterator)->setPosition({ position.x,position.y });
			}
		}
	}

	bool RealTimeBattle::_checkPlacementCollisions(std::list<std::shared_ptr<Character>>::iterator character)
	{
		sf::Vector2f position;
		position.x = ((2 * (*character)->getPosition().y + (*character)->getPosition().x) / 2) / 25;
		position.y = ((2 * (*character)->getPosition().y - (*character)->getPosition().x) / 2) / 25;
		if (position.x > _tile_map->getHeight() || position.x < 0 ||
			position.y > _tile_map->getWidth() || position.y < 0) //checks if character is not situated "inside" the map
			return true;//collides
		else 
			return false;// do not collides
	}

	bool RealTimeBattle::_isEnemyTeamDead()
	{
		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_enemies.begin(); iterator != _list_of_enemies.end(); iterator++)
		{
			if ((*iterator)->isAlive())
				return false;
		}
		return true;
	}

	bool RealTimeBattle::_isAllyTeamDead()
	{
		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_allies.begin(); iterator != _list_of_allies.end(); iterator++)
		{
			if ((*iterator)->isAlive())
				return false;
		}
		return true;
	}

	std::list<std::shared_ptr<Character>>::iterator RealTimeBattle::_pickRandomAlly()
	{
		auto start = _list_of_allies.begin(), end = _list_of_allies.end();
		unsigned seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		std::mt19937 gen(seed);
		std::uniform_int_distribution<int> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}

	void RealTimeBattle::_charactersUpdatesAndRenders()
	{
		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_enemies.begin(); iterator != _list_of_enemies.end(); iterator++)
		{
			if(!(*iterator)->isAlive())
				(*iterator)->deadBody(*_window);
		}

		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_allies.begin(); iterator != _list_of_allies.end(); iterator++)
		{
			if (!(*iterator)->isAlive())
				(*iterator)->deadBody(*_window);
		}

		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_enemies.begin(); iterator != _list_of_enemies.end(); iterator++)
		{
			if ((*iterator)->isAlive())
			{
				(*iterator)->update(_clock.getElapsedTime(), _tile_map->getCollidableObjects(), _list_of_allies, *_window);
				(*iterator)->dealDamage(_clock.getElapsedTime(), _list_of_allies, *_window);
				(*iterator)->render(*_window);
			}
		}

		for (std::list<std::shared_ptr<Character>>::iterator iterator = _list_of_allies.begin(); iterator != _list_of_allies.end(); iterator++)
		{
			if ((*iterator)->isAlive())
			{
				(*iterator)->update(_clock.getElapsedTime(), _tile_map->getCollidableObjects(), _list_of_enemies, *_window);
				(*iterator)->dealDamage(_clock.getElapsedTime(), _list_of_enemies, *_window);
				(*iterator)->render(*_window);
			}
		}
	}

	RealTimeBattle::RealTimeBattle(sf::RenderWindow& window) :
		_player(nullptr), _tile_map(nullptr), _user_interface(nullptr), _is_paused(false), _is_surrendered(false), _return_from_battle(false), _is_ally_choosen(false)
	{
		_window = &window;
		_camera.reset(sf::FloatRect(0, 0, 1280, 720));
		_user_interface = std::make_unique<RTBGUI::GUI>(window);
		_asset_manager.setTexture("player", "img/character.png");
		_asset_manager.setTexture("enemy_swordsman", "img/enemy_swordsman.png");
		_asset_manager.setTexture("ally_swordsman", "img/ally_swordsman.png");
		_asset_manager.setTexture("enemy_archer", "img/enemy_archer.png");
		_asset_manager.setTexture("ally_archer", "img/ally_archer.png");
		_asset_manager.setTexture("ally_spearman", "img/ally_spearman.png");
		_asset_manager.setTexture("enemy_spearman", "img/enemy_spearman.png");
		_asset_manager.setTexture("arrow", "img/arrow.png");
		_asset_manager.setTexture("window_border", "img/WindowBorder.png");
	}

	RealTimeBattle::~RealTimeBattle()
	{
		_window = nullptr;
	}

	void RealTimeBattle::mainLoop()
	{
		_tile_map = std::unique_ptr<TileMap>(new TileMap({ 50,50 }));
		this->_armyCreation();
		_camera.zoom(static_cast<float>(0.8));
		_audio_manager.playMusic("audio/mainTheme.wav", 20.f);
		while (_window->isOpen())
		{
			while (_window->pollEvent(_event)) //handling events
			{
				if (_event.type == sf::Event::EventType::Closed)
					_window->close();
				if (_event.type == sf::Event::MouseWheelMoved)
					this->_zoomEvent();
				if (_event.type == sf::Event::KeyPressed)
				{
					if (_event.key.code == sf::Keyboard::Escape)
					{
						if (_is_paused)
							_is_paused = false;
						else
							_is_paused = true;
					}
				}

				if (_event.type == sf::Event::MouseButtonPressed)
				{
					sf::Vector2f center = _camera.getCenter();
					sf::Vector2f worldPos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
					if (_event.mouseButton.button == sf::Mouse::Left && _user_interface->getButtonNo()->getSprite().getGlobalBounds().contains(worldPos) && _is_paused)
					{
						_is_paused = false;
					}
					else if (_event.mouseButton.button == sf::Mouse::Left && _user_interface->getButtonYes()->getSprite().getGlobalBounds().contains(worldPos) && _is_paused)
					{
						_is_paused = false;
						_is_surrendered = true;
					}
					else if (_event.mouseButton.button == sf::Mouse::Left && _user_interface->getButtonOk()->getSprite().getGlobalBounds().contains(worldPos) && (this->_isAllyTeamDead() || _is_surrendered))
						_return_from_battle = true;
					else if (_event.mouseButton.button == sf::Mouse::Left && _user_interface->getButtonOk()->getSprite().getGlobalBounds().contains(worldPos) && this->_isEnemyTeamDead())
						_return_from_battle = true;
					else if (_event.mouseButton.button == sf::Mouse::Left && !this->_isAllyTeamDead() && !this->_isEnemyTeamDead() && !_player->isAlive())
					{
						_choosen_ally = _pickRandomAlly();
						while(!(*_choosen_ally)->isAlive())
							_choosen_ally = _pickRandomAlly();
						_is_ally_choosen = true;
					}
					else if (_event.mouseButton.button == sf::Mouse::Right && _user_interface->getButtonBook()->getSprite().getGlobalBounds().contains(worldPos) && !_is_paused)
					{
						if (_user_interface->isLeftPanelShown())
							_user_interface->showLeftPanel(false);
						else
							_user_interface->showLeftPanel(true);
					}
				}
				if (_event.type == sf::Event::LostFocus)
					_is_paused = true;
			}

			_window->clear();
			if (!_is_paused)
			{
				_window->setView(_camera);

				//Drawing first layer of map
				_tile_map->drawTiles(*_window);

				//Bots
				if (_player->isAlive())
				{
					_user_interface->setCameraCenter(_player->getPosition());
					_camera.setCenter(_player->getPosition()); //camera is centered on the player
				}
				else if (_is_ally_choosen)
				{
					_user_interface->setCameraCenter((*_choosen_ally)->getPosition());
					_camera.setCenter((*_choosen_ally)->getPosition());
				}

				this->_charactersUpdatesAndRenders();

				_tile_map->drawObjects(*_window);
			}
			//Updating and drawing user interface
			_window->setView(_user_interface->getCamera());

			_user_interface->update(_is_paused, _is_surrendered, this->_isAllyTeamDead(), this->_isEnemyTeamDead(), _return_from_battle);
			_user_interface->render(_is_paused, _is_surrendered, this->_isAllyTeamDead(), this->_isEnemyTeamDead());

			//Displaying everything
			_window->display();

			if ((_return_from_battle && this->_isAllyTeamDead()) || (_return_from_battle && _is_surrendered))
			{ 
				return;
			}
			else if (_return_from_battle && this->_isEnemyTeamDead())
			{
				return;
			}
		}
	}
}