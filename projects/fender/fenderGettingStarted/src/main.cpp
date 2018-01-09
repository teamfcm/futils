# include "fender.hpp"

int main(int, char **av)
{
  fender::Fender engine(av[0]);

  if (engine.start() != 0)
    return 1;
  engine.run();
  return 0;
}
