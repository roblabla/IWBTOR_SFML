#include "ResMan.hpp"

template<typename T>
T* ResMan::getRes(std::string id) {
  static_assert(true, "You need to use one of the existing specialization");
}

template<>
sf::Texture* ResMan::getRes<sf::Texture>(std::string id) {
  auto tex = new sf::Texture;
  tex->loadFromFile("res/images/" + id + ".png");
  return tex;
}

template<>
sf::Font* ResMan::getRes<sf::Font>(std::string id) {
  auto tex = new sf::Font;
  tex->loadFromFile("res/fonts/" + id + ".ttf");
  return tex;
}
