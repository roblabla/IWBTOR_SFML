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
  _keyboardKeys = {{sf::Keyboard::W, Action::Up},
                   {sf::Keyboard::A, Action::Left},
                   {sf::Keyboard::S, Action::Down},
                   {sf::Keyboard::D, Action::Right},
                   {sf::Keyboard::Space, Action::Jump},
                   {sf::Keyboard::Escape, Action::Pause}};
  _joystickAxis = {{sf::Joystick::Axis::X, std::make_tuple(Action::Left, Action::Right)},
                   {sf::Joystick::Axis::Y, std::make_tuple(Action::Up, Action::Down)}};
  _joystickKeys = {{0, Action::Jump},
                   {7, Action::Pause}};
}

Action Settings::getAction(/*std::string type, */sf::Keyboard::Key key) {
  if (_keyboardKeys.count(key)) {
    return _keyboardKeys[key];
  } else {
    return Action::None;
  }
}

Action Settings::getAction(/*std::string type, */uint32_t button) {
  if (_joystickKeys.count(button)) {
    return _joystickKeys[button];
  } else {
    return Action::None;
  }
}

Action Settings::getAction(/*std::string type, */sf::Joystick::Axis axis, float position) {
  if (_joystickAxis.count(axis)) {
    if (position < -50) {
      return std::get<0>(_joystickAxis[axis]);
    } else {
      return std::get<1>(_joystickAxis[axis]);
    }
  } else {
    return Action::None;
  }
}

CEREAL_CLASS_VERSION(Settings, 1);
