#include "Game.hpp"
#include "MenuState.hpp"
#include <SFML/Graphics.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>

Game::Game() {
  _w.create(sf::VideoMode(800, 600), "Platformer");
  std::ifstream settingsFile("settings.txt");
  if (settingsFile) {
    cereal::BinaryInputArchive in(settingsFile);
    in(_settings);
    settingsFile.close();
  }
  this->windowInit();
}

Settings Game::getSettings() {
  return _settings;
}

void Game::windowInit() {
  this->_w.setFramerateLimit(60);
  this->_w.setVerticalSyncEnabled(true);
  this->_w.setKeyRepeatEnabled(false);
  sf::Image image;
  image.loadFromFile("res/images/icon.png");
  this->_w.setIcon(32, 32, image.getPixelsPtr());
}

void Game::draw(sf::Drawable& toDraw) {
  this->_w.draw(toDraw);
}

void Game::runMainLoop() {
  // First the ScrollingMenuState
  sf::Font font;
  font.loadFromFile("res/fonts/arial.ttf");
  this->_state = new MenuState(*this, font, "res/images/menuBg.png", {"Exit"}); // TODO : Delete
  while (this->_w.isOpen()) {
    sf::Event ev;
    while (this->_w.pollEvent(ev)) {
      if (ev.type == sf::Event::Closed) {
        _w.close();
      }
      this->_state->onEvent(ev);
    }
    this->_state->update();
    this->_w.clear(sf::Color::Black);
    this->_state->draw();
    this->_w.display();
  }
}
