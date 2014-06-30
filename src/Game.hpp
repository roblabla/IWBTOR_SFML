#ifndef GAME_HPP
#define GAME_HPP

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "Settings.hpp"
#include "IState.hpp"

class Game {
public:
  Game();
  void runMainLoop();
  void draw(sf::Drawable& toDraw);
  sf::RenderWindow& getWindow();
  sf::Texture* getTexture(std::string id);
  Settings getSettings();
  void stopInput(std::chrono::milliseconds);
private:
  void windowInit();
  void handleEvents();
  Settings _settings;
  sf::RenderWindow _w;
  sf::Music _bgMusic;
  std::shared_ptr<IState> _state;
  std::multiset<Action> _inputState;
  std::chrono::time_point<std::chrono::steady_clock> _stopInput;
};

#endif
