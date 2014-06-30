#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include<string>
#include <map>
#include <tuple>
#include <SFML/Window.hpp>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
enum Action {
  Use,
  Up,
  Down,
  Left,
  Right,
  Jump,
  Pause,
  None
};

class Settings
{
public:
  Settings();
  bool drawTextures;
  unsigned int videoModeWidth;
  unsigned int videoModeHeight;
  float musicVolume;
  float soundVolume;
  bool leaderboardLocal;
  std::string username;
  Action getAction(/*std::string type, */sf::Keyboard::Key ev);
  Action getAction(/*std::string type, */sf::Joystick::Axis ev, float pos);
  Action getAction(/*std::string type, */uint32_t ev);
private:
  std::map<sf::Keyboard::Key, Action> _keyboardKeys;
  std::map<uint32_t, Action> _joystickKeys;
  std::map<sf::Joystick::Axis, std::tuple<Action, Action>> _joystickAxis;

  friend class cereal::access;
  template<class Archive>
  void serialize(Archive& ar, uint32_t const version) {
    if (version == 1) {
      ar(CEREAL_NVP(drawTextures), CEREAL_NVP(videoModeWidth),
         CEREAL_NVP(videoModeHeight), CEREAL_NVP(musicVolume),
         CEREAL_NVP(soundVolume), CEREAL_NVP(leaderboardLocal),
         CEREAL_NVP(username), cereal::make_nvp("keyboardKeys", _keyboardKeys),
         cereal::make_nvp("joystickKeys", _joystickKeys));
    } else {
      throw 1;
    }
  }

};

#endif // SETTINGS_HPP
