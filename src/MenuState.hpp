#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "IState.hpp"
#include "Game.hpp"
#include<functional>
#include<initializer_list>
#include<string>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Settings.hpp"

class MenuState : public IState {
public:
  MenuState(Game& game, std::string font, std::string img, std::initializer_list<std::string> args);
  
  // IState
  void initialize();
  void update();
  void draw();
  void onEvent(sf::Event);
  void onEvent(Action);
  void uninitialize();

  void onItemSelected(std::function<void(int)>);

private:
  std::function<void(int)> _onItemSelected;
  sf::Sprite _background;
  std::vector<sf::Text> _menuBtns;
  int _selectedPos;
  Game& _game;
  std::shared_ptr<sf::Font> _font;
};

#endif
