#include <iostream>

class Actionable {
public:
  Actionable() : m_identifier(0xba3e) {
  }
  virtual void take_action() const {
    std::cout << "Taking a generic action (" << m_identifier << ")!\n";
  }
  virtual void default_action() const {
    std::cout << "Taking a generic default action (" << m_identifier << ")!\n";
  }

private:
  int m_identifier;
};

class Mathematic : public Actionable {
public:
  Mathematic() : m_identifier{0xde71} {
  }
  virtual void take_action() const {
    std::cout << "Taking a mathematic action (" << m_identifier << ")!\n";
  }
  virtual void take_mathematic_action() const {
    std::cout << "Taking a mathematic action - specific (" << m_identifier << ")!\n";
  }

private:
  int m_identifier;
};

class Add : public Mathematic {
public:
  Add() : m_identifier(0xadd) {
  }
  void take_action() const override {
    std::cout << "Taking an add action (" << m_identifier << ")!\n";
  }

private:
  int m_identifier;
};

class Append : public Actionable {
public:
  Append() : m_identifier(2) {
  }
  virtual void take_action() const {
    std::cout << "Taking an append action (" << m_identifier << ")!\n";
  }
  virtual void default_action() const {
    std::cout << "Taking an append default action (" << m_identifier << ")!\n";
  }
private:
  int m_identifier;
};

void actionate(const Actionable &actionable) {
  actionable.default_action();
  actionable.take_action();
}

int main() {
  Actionable generic_actionable{};
  Add add_actionable{};
  Append append_actionable{};

  std::cout << "actionate(generic_actionable):\n";
  actionate(generic_actionable);
  std::cout << "actionate(add_actionable):\n";
  actionate(add_actionable);
  std::cout << "actionate(append_actionable):\n";
  actionate(append_actionable);

  return 0;
}
