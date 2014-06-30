#ifndef RESMAN_HPP
#define RESMAN_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Utils.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/archives/json.hpp"
#include "tinydir.h"

struct AnimationInformation {
  int top;
  int width;
  int height;
  int interval;
  int frames;

private:
  friend class cereal::access;
  template<class Archive>
  void serialize(Archive& ar, uint32_t const version) {
    if (version == 1) {
      ar(CEREAL_NVP(top), CEREAL_NVP(width), CEREAL_NVP(height),
         CEREAL_NVP(interval), CEREAL_NVP(frames));
    } else {
      throw 1;
    }
  }
};

struct SpriteInformation {
  std::vector<AnimationInformation> animations;
  sf::Color color;
  bool texturesPerAnim;

private:
  friend class cereal::access;

  template<class Archive>
  void serialize(Archive& ar, uint32_t const version) {
    if (version == 1) {
      ar(CEREAL_NVP(animations), CEREAL_NVP(color), CEREAL_NVP(texturesPerAnim));
    } else {
      throw 1;
    }
  }
};

CEREAL_CLASS_VERSION(AnimationInformation, 1)
CEREAL_CLASS_VERSION(SpriteInformation, 1)

class ResMan {
public:
  static class _init {
  public:
    _init();
  } _initializer;
  // TODO : Use unique_ptr instead.
  template<typename T> static std::shared_ptr<T> getRes(std::string id);
private:
  static std::map<std::string, SpriteInformation> _spriteInfos;
  static std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
  static std::map<std::string, std::shared_ptr<sf::Font>> _fonts;
};

template<>
std::shared_ptr<sf::Texture> ResMan::getRes<sf::Texture>(std::string id);

template<>
std::shared_ptr<sf::Font> ResMan::getRes<sf::Font>(std::string id);

#endif
