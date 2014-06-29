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

sf::RenderWindow& Game::getWindow() {
  return this->_w;
}

void Game::draw(sf::Drawable& toDraw) {
  this->_w.draw(toDraw);
}

void Game::runMainLoop() {
  // First the ScrollingMenuState
  sf::Font font;
  font.loadFromFile("res/fonts/Square.ttf");
  this->_state = std::make_shared<MenuState>(MenuState(*this, "Square", "menuBg", {"Play", "Exit"}));
  std::dynamic_pointer_cast<MenuState> (this->_state)->onItemSelected([this](int x) {
    if (x == 1) {
      this->_w.close();
    }
  });
  while (this->_w.isOpen()) {
    this->handleEvents();
    if (_stopInput < std::chrono::steady_clock::now()) {
      for (auto act : _inputState) { // TODO : Concurrent modification.
        this->_state->onEvent(act);
      }
    }
    this->_state->update();
    this->_w.clear(sf::Color::Black);
    this->_state->draw();
    this->_w.display();
  }
}

void Game::stopInput(std::chrono::milliseconds ms) {
  _stopInput = std::chrono::steady_clock::now() + ms;
}

void Game::handleEvents() {
  sf::Event ev;
  while (this->_w.pollEvent(ev)) {
    switch (ev.type) {
      case sf::Event::Closed:
        _w.close();
        break;

      case sf::Event::LostFocus:
        _inputState.clear();
        break;

      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
      {
        auto action = _settings.getAction(ev.key.code);
        if (action != Action::None) {
          if (ev.type == sf::Event::KeyPressed)
            _inputState.insert(action);
          else {
            auto pos = _inputState.find(action);
            if (pos != _inputState.end()) {
              _inputState.erase(pos);
            }
          }
        }
        break;
      }
      case sf::Event::JoystickButtonPressed:
      case sf::Event::JoystickButtonReleased:
      {
        auto action = _settings.getAction(ev.joystickButton.button);
        if (action != Action::None) {
          if (ev.type == sf::Event::JoystickButtonPressed)
            _inputState.insert(action);
          else {
            auto pos = _inputState.find(action);
            if (pos != _inputState.end()) {
              _inputState.erase(pos);
            }
          }
        }
        break;
      }
     /* case sf::Event::JoystickMoved:
        auto action = _settings.getAction(ev.joystickMove.axis, ev.joystickMove.position);
        if (action != Action::None) {

          _inputState.insert(action);
        }*/
    }
    this->_state->onEvent(ev);
  }
}
