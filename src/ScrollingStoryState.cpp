#include "ScrollingStoryState.hpp"

ScrollingStoryState::ScrollingStoryState(Game& game)
  : _game(game)
{

}

void ScrollingStoryState::initialize() {
  _music.openFromFile("res/music/iwbtg/megaman1.ogg");
  _iwbtgMenuBg.setTexture(*ResMan::getRes<sf::Texture>("iwbtgMenuBg"));
  _view = sf::View(sf::Vector2f(), sf::Vector2f(800, 600));
  _music.play();
}

void ScrollingStoryState::update() {

}

void ScrollingStoryState::draw() {
  _game.getWindow().setView(_view);
  _game.draw(_iwbtgMenuBg);
}

void ScrollingStoryState::onEvent(sf::Event) {

}

void ScrollingStoryState::onEvent(Action) {

}

void ScrollingStoryState::uninitialize() {
  // Deallocate resources.
}
