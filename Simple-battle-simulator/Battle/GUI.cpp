#pragma once

#include "GUI.h"

namespace RTBGUI
{
	GUI::GUI(sf::RenderWindow& window) :
		_window(&window), _show_left_panel(true)
	{
		_window_border = std::make_unique<WindowBorder>();
		_menu = std::make_unique<Menu>();
		_cursor = std::make_unique<Cursor>();
		_panel = std::make_unique<Panel>();
		_book = std::make_shared<BookButton>();
		_button_yes = std::make_shared<Button>("YES");
		_button_no = std::make_shared<Button>("NO");
		_button_ok = std::make_shared<Button>(" OK");
		_message_menu = std::make_unique<Message>("  Do you really \nwant to surrender?", 40);
		_message_lost = std::make_unique<Message>("    You Lost", 40);
		_message_won = std::make_unique<Message>("    You won", 40);

		_asset_manager.setTexture("menuBackground", "img/menuBackground.png");
		_menu_background.setTexture(_asset_manager.getTexture("menuBackground"));
		_asset_manager.setTexture("lostBackground", "img/lostBackground.png");
		_lost_background.setTexture(_asset_manager.getTexture("lostBackground"));
		_asset_manager.setTexture("wonBackground", "img/wonBackground.png");
		_won_background.setTexture(_asset_manager.getTexture("wonBackground"));

		_window->setMouseCursorVisible(false);

		_camera.reset(sf::FloatRect(0, 0, 1280, 720));
	}

	GUI::~GUI()
	{
		_window = nullptr;
	}

	void GUI::update(bool& is_paused, bool& is_surrendered, bool ally_team_dead, bool enemy_team_dead, bool& return_from_battle)
	{
		sf::Vector2f center = _camera.getCenter();
		sf::Vector2f worldPos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
		_cursor->update(worldPos);
		_window_border->update(sf::Vector2f(center.x - 640.f, center.y - 360.f));
		if (is_paused)
		{
			_message_menu->update(sf::Vector2f(center.x - 139.f, center.y - 100.f));
			_menu_background.setPosition(center.x - 640.f, center.y - 360.f);
			_menu->update(sf::Vector2f(center.x - 160.f, center.y - 240.f));
			_button_yes->update(sf::Vector2f(center.x - 139.f, center.y + 40.f));
			_button_no->update(sf::Vector2f(center.x - 139.f, center.y + 100.f));

			if (_button_no->getSprite().getGlobalBounds().contains(worldPos))
				_button_no->setHovered(true);
			else if (_button_yes->getSprite().getGlobalBounds().contains(worldPos))
				_button_yes->setHovered(true);
		}
		else if (ally_team_dead || is_surrendered)
		{
			_lost_background.setPosition(center.x - 640.f, center.y - 360.f);
			_menu->update(sf::Vector2f(center.x - 160.f, center.y - 240.f));
			_message_lost->update(sf::Vector2f(center.x - 139.f, center.y - 100.f));
			_button_ok->update(sf::Vector2f(center.x - 139.f, center.y + 40.f));
			if (_button_ok->getSprite().getGlobalBounds().contains(worldPos))
				_button_ok->setHovered(true);
		}
		else if (enemy_team_dead)
		{
			_won_background.setPosition(center.x - 640.f, center.y - 360.f);
			_menu->update(sf::Vector2f(center.x - 160.f, center.y - 240.f));
			_message_won->update(sf::Vector2f(center.x - 139.f, center.y - 100.f));
			_button_ok->update(sf::Vector2f(center.x - 139.f, center.y + 40.f));
			if (_button_ok->getSprite().getGlobalBounds().contains(worldPos))
				_button_ok->setHovered(true);
		}
		else if (!is_paused)
		{
			_book->update(sf::Vector2f(center.x + 560.f, center.y - 335.f));
			if (_book->getSprite().getGlobalBounds().contains(worldPos))
				_book->setHovered(true);
			_panel->update(sf::Vector2f(center.x - 636.f, center.y - 321.f));
		}
	}

	void GUI::render(bool& is_paused, bool& is_surrendered, bool ally_team_dead, bool enemy_team_dead)
	{
		_window_border->render(_window);
		if (is_paused)
		{
			_window->draw(_menu_background);
			_window_border->render(_window);
			_menu->render(_window);
			_button_yes->render(_window);
			_button_no->render(_window);
			_message_menu->render(_window);
		}
		else if (ally_team_dead || is_surrendered)
		{
			_window->draw(_lost_background);
			_window_border->render(_window);
			_menu->render(_window);
			_button_ok->render(_window);
			_message_lost->render(_window);
		}
		else if (enemy_team_dead)
		{
			_window->draw(_won_background);
			_window_border->render(_window);
			_menu->render(_window);
			_button_ok->render(_window);
			_message_won->render(_window);
		}
		else if (!is_paused)
		{
			_book->render(_window);
			if (_show_left_panel)
				_panel->render(_window);
		}
		_cursor->render(_window);
	}

	void GUI::setCameraZoom(float zoom)
	{
		_camera.zoom(zoom);
	}

	void GUI::setCameraCenter(sf::Vector2f center)
	{
		_camera.setCenter(center);
	}

	void GUI::showLeftPanel(bool show)
	{
		_show_left_panel = show;
	}

	bool GUI::isLeftPanelShown()
	{
		return _show_left_panel;
	}

	sf::View GUI::getCamera()
	{
		return _camera;
	}

	std::shared_ptr<Button> GUI::getButtonNo()
	{
		return _button_no;
	}

	std::shared_ptr<Button> GUI::getButtonYes()
	{
		return _button_yes;
	}

	std::shared_ptr<Button> GUI::getButtonOk()
	{
		return _button_ok;
	}

	std::shared_ptr<BookButton> GUI::getButtonBook()
	{
		return _book;
	}
}