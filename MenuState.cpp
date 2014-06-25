#include "MenuState.hpp"

MenuState::MenuState(Game& game, sf::Font font, std::string img, std::initializer_list<std::string> args) :
  _game(game) {
  sf::Texture tex;
  tex.loadFromFile(img);
  this->_background.setTexture(tex);
  this->_menuBtns.resize(args.size());
  for (auto myStr : args) {
    this->_menuBtns.push_back(sf::Text(myStr, font));
  }
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
                                      150 :
                                      255));
    _game.draw(_menuBtns[i]);
  }
  // Draw the carrets
}

void MenuState::onEvent(sf::Event) {

}

void MenuState::uninitialize() {

}
