#include <iostream>

class Vehicle {
public:
  Vehicle() : m_price{0xba3e} {};
  virtual bool needs_gas() { return true; }

private:
  int m_price;
};

class EV : public Vehicle {
public:
  EV() : m_price{0xe11} {};
  bool needs_gas() final { return false; }

private:
  int m_price;
};

class Tesla : public EV {
public:
  Tesla() : m_price{0x7e31a} {};

private:
  int m_price;
};

class Semi : public Vehicle {
public:
  Semi() : m_price{0x1073} {};
  virtual bool needs_gas() { return false; }

private:
  int m_price;
};

void print_if_needs_gas(Vehicle &vehicle) {
  if (vehicle.needs_gas()) {
    std::cout << "This vehicle needs gas.\n";
  } else {
    std::cout << "This vehicle does not need gas.\n";
  }
}

void print_if_does_not_need_gas(Vehicle &vehicle) {
  if (vehicle.needs_gas()) {
    std::cout << "This vehicle needs gas.\n";
  } else {
    std::cout << "This vehicle does not need gas.\n";
  }
}


int main() {
  Semi semi{};
  Tesla tesla{};
  EV ev{};

  print_if_does_not_need_gas(semi);
  print_if_needs_gas(semi);
  print_if_needs_gas(tesla);
  print_if_needs_gas(ev);

  return 0;
}
