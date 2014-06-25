#ifndef GAME_HPP
#define GAME_HPP

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include "IState.hpp"
#include "Settings.hpp"

class Game {
public:
  Game();
  void runMainLoop();
  void draw(sf::Drawable& toDraw);
  Settings getSettings();
private:
  void windowInit();
  void handleEvents();
  Settings _settings;
  sf::RenderWindow _w;
  sf::Music _bgMusic;
  IState* _state;
};

#endif
