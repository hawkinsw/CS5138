#include <iostream>

class Squirrel {
public:
  virtual char *getColor() const { return "brown"; }
  virtual bool canFly() const { return false; }

  virtual unsigned int acornCapacity() const { return 2; }
};

class AnimatedSquirrel : public Squirrel {
public:
  virtual char *getColor() const { return "gray"; }
  virtual bool canFly() const { return true; }
  virtual unsigned int acornCapacity() const { return (unsigned int)-1; }
};

class AlbinoSquirrel : public Squirrel {
public:
  virtual char *getColor() const { return "white"; }
};

int main() {
  AnimatedSquirrel rocky{};
  AlbinoSquirrel snowy{};
  Squirrel oh_where{};

  printf("Rocky is %s\n", rocky.getColor());

  return 0;
}