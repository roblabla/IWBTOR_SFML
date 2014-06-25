#include "settings.hpp"
#include <SFML/Window.hpp>

Settings::Settings() {
  bool drawTextures = true;
  unsigned int videoModeWidth = 800;
  unsigned int videoModeHeight = 600;
  float musicVolume = .50f;
  float soundVolume = .50f;
  bool leaderboardLocal = false;
  std::string username = "Player";
}

Action Settings::getAction(std::string type, sf::Keyboard::Key key) {
  if (_keyboardKeys.count(type) && _keyboardKeys[type].count(key)) {
    return _keyboardKeys[type][key];
  } else if (_keyboardKeys[""].count(key)){
    return _keyboardKeys[""][key];
  } else {
    return Action::None;
  }
}

CEREAL_CLASS_VERSION(Settings, 1);
