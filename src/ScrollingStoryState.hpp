#ifndef SCROLLINGSTORYSTATE_HPP
#define SCROLLINGSTORYSTATE_HPP

#include "Game.hpp"
#include "IState.hpp"
#include "ResMan.hpp"

class ScrollingStoryState : public IState
{
public:
  ScrollingStoryState(Game&);

  // IState
  void initialize();
  void update();
  void draw();
  void onEvent(sf::Event);
  void onEvent(Action);
  void uninitialize();
private:
  Game& _game;
  sf::Sprite _iwbtgMenuBg;
  std::vector<sf::Sprite> _iwbtgSprites;
  sf::View _view;
  sf::Music _music;
};

#endif // SCROLLINGSTORYSTATE_HPP
