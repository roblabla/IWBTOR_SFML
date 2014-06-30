#include "MenuState.hpp"
#include "ResMan.hpp"

MenuState::MenuState(Game& game, std::string font, std::string img, std::initializer_list<std::string> args) :
  _game(game) {
  _font = ResMan::getRes<sf::Font>(font);
  this->_background.setTexture(*ResMan::getRes<sf::Texture>(img));
  sf::View _view = game.getWindow().getDefaultView();
  int i = 0;
  for (auto myStr : args) {
    auto btn = sf::Text(myStr, *_font);
    btn.setCharacterSize(_view.getSize().y / 12);
    btn.setColor(sf::Color::White);
    auto iWidth = btn.getLocalBounds().width;
    auto iHeight = btn.getCharacterSize();
    btn.setPosition(sf::Vector2f(_view.getSize().x/2 - iWidth/2,
        _view.getSize().y / 2 - args.size() * iHeight / 2 + i * iHeight));
    this->_menuBtns.push_back(btn);
    i++;
  }

  _background.setScale(sf::Vector2f(_view.getSize().x/_background.getLocalBounds().width,
                  _view.getSize().y/_background.getLocalBounds().height));
}

void MenuState::initialize() {

}

void MenuState::update() {
}

void MenuState::draw() {
  this->_game.draw(this->_background);
  for (int i = 0; i < _menuBtns.size(); i++) {
    _menuBtns[i].setColor(sf::Color(_menuBtns[i].getColor().r,
                                    _menuBtns[i].getColor().g,
                                    _menuBtns[i].getColor().b,
                                    _selectedPos == i ?
                                      255 :
                                      140));

/*    sf::RectangleShape shape (sf::Vector2f(
                                _menuBtns[i].getGlobalBounds().width,
                                _menuBtns[i].getGlobalBounds().height));
    shape.setPosition(_menuBtns[i].getPosition());
    shape.setFillColor(sf::Color::Red);
    _game.draw(shape);*/
    _game.draw(_menuBtns[i]);
  }
  // Draw the carrets
}

void MenuState::onEvent(sf::Event ev) {
  if (ev.type == sf::Event::MouseMoved) {
    for (auto i = 0; i < _menuBtns.size(); i++) {
      sf::Text btn = _menuBtns[i];
      if (btn.getPosition().x < ev.mouseMove.x && ev.mouseMove.x < btn.getPosition().x + btn.getGlobalBounds().width
       && btn.getPosition().y < ev.mouseMove.y && ev.mouseMove.y < btn.getPosition().y + btn.getGlobalBounds().height) {
        _selectedPos = i;
      }
    }
  } else if (ev.type == sf::Event::MouseButtonPressed) {
    for (auto i = 0; i < _menuBtns.size(); i++) {
      sf::Text btn = _menuBtns[i];
      if (btn.getPosition().x < ev.mouseMove.x && ev.mouseMove.x < btn.getPosition().x + btn.getGlobalBounds().width
       && btn.getPosition().y < ev.mouseMove.y && ev.mouseMove.y < btn.getPosition().y + btn.getGlobalBounds().height) {
        _onItemSelected(_selectedPos);
      }
    }
  }
}

void MenuState::onEvent(Action ev) {
  switch(ev) {
    case Up:
      _selectedPos = --_selectedPos % _menuBtns.size();
      break;
    case Down:
      _selectedPos = ++_selectedPos % _menuBtns.size();
      break;
    case Jump:
      if (_onItemSelected) _onItemSelected(_selectedPos);
      break;
  }
  this->_game.stopInput(std::chrono::milliseconds(150));
}

void MenuState::onItemSelected(std::function<void(int)> func) {
  this->_onItemSelected = func;
}

void MenuState::uninitialize() {

}
