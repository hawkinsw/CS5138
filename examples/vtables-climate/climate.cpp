#include <iostream>

enum class PrecipType { NONE, RAIN, SNOW };

class Climate {
public:
  virtual PrecipType getPrecipType() const { return PrecipType::NONE; }
};

class Tropical : public Climate {
public:
  PrecipType getPrecipType() const override { return PrecipType::NONE; }
};

class Desert : public Climate {
  // Nothing!
};

bool needUmbrella(const Climate &c) {
  return c.getPrecipType() != PrecipType::NONE;
}

int main() {

  Desert sahara{};
  Tropical bali{};

  if (needUmbrella(sahara)) {
    std::cout << "I need an umbrella in the desert!\n";
  } else {
    std::cout << "It never rains in Indian Wells\n";
  }

  return 0;
}
