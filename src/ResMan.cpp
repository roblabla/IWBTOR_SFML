#include "ResMan.hpp"

std::map<std::string, SpriteInformation> ResMan::_spriteInfos;
std::map<std::string, std::shared_ptr<sf::Texture>> ResMan::_textures;
std::map<std::string, std::shared_ptr<sf::Font>> ResMan::_fonts;

ResMan::_init::_init() {
  tinydir_dir dir;
  tinydir_open(&dir, "res/sprites");
  while (dir.has_next) {
    tinydir_file file;
    tinydir_readfile(&dir, &file);
    if (file.extension == "json") {
      std::ifstream fileStream(std::string(file.path) + std::string(file.name));
      cereal::JSONInputArchive iarchive(fileStream);
      SpriteInformation spriteInfo;
      iarchive(spriteInfo);
      ResMan::_spriteInfos[file.name] = spriteInfo;
      fileStream.close();
    } else if (file.is_dir) {
      // open subdir, needs to be recursive.
    }
    tinydir_next(&dir);
  }
  tinydir_close(&dir);
}

template<typename T>
std::shared_ptr<T> ResMan::getRes(std::string id) {
  static_assert(true, "You need to use one of the existing specialization");
}

template<>
std::shared_ptr<sf::Texture> ResMan::getRes<sf::Texture>(std::string id) {
  if (ResMan::_textures.count(id)) {
    return ResMan::_textures[id];
  } /*else if (ResMan::_spriteInfos.count(id)) {
    // TODO : SpriteInfo stuff.
  } */else {
    auto tex = std::make_shared<sf::Texture>();
    if (tex->loadFromFile("res/images/" + id + ".png")) {
      ResMan::_textures[id] = tex;
      return tex;
    } else {
      return std::shared_ptr<sf::Texture>();
    }
  }
}

template<>
std::shared_ptr<sf::Font> ResMan::getRes<sf::Font>(std::string id) {
  auto tex = std::make_shared<sf::Font>(sf::Font());
  tex->loadFromFile("res/fonts/" + id + ".ttf");
  return tex;
}
