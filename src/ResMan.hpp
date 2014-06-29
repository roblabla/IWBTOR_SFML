#include <SFML/Graphics.hpp>

class ResMan {
public:
  template<typename T> static T* getRes(std::string id);
private:
};

template<>
sf::Texture* ResMan::getRes<sf::Texture>(std::string id);

template<>
sf::Font* ResMan::getRes<sf::Font>(std::string id);
