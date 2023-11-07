#include "Org.h"
#include "emp/Evolve/World.hpp"
#include "emp/math/Random.hpp"
#include "emp/math/random_utils.hpp"

class Hare : public Organism {
  public:
    Hare(emp::Ptr<emp::Random> _random, double _points = 0)
        : Organism(_random, _points) {
        species = "Hare";
    }

    bool ShouldIMove() override {
        double rand = random->GetDouble();
        return rand > 0.2;
    }

    std::string GetColor() override {
        return "blue";
    }
};