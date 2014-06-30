#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>
#include "cereal/cereal.hpp"
#include <string>

namespace cereal {
  template<class Archive>
  void serialize(Archive& ar, sf::Color& color) {
    ar(cereal::make_nvp("a", color.a),
       cereal::make_nvp("r", color.r),
       cereal::make_nvp("g", color.g),
       cereal::make_nvp("b", color.b));
  }
}

bool hasEnding(std::string const&, std::string const&);

#endif // UTILS_HPP
