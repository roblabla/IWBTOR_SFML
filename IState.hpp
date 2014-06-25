#ifndef ISTATE_HPP
#define ISTATE_HPP

#include<string>
#include<SFML/Window.hpp>
class IState {
public:
  virtual std::string getBgMusic() { return ""; }
  virtual void initialize() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void onEvent(sf::Event) = 0;
  virtual void uninitialize() = 0;
  virtual ~IState(){}
};

#endif
