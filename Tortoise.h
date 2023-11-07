#include "Org.h"
#include "emp/Evolve/World.hpp"
#include "emp/math/Random.hpp"
#include "emp/math/random_utils.hpp"

class Tortoise : public Organism {
  public:
    Tortoise(emp::Ptr<emp::Random> _random, double _points = 0)
        : Organism(_random, _points) {
        species = "Tortoise";
    }

    bool ShouldIMove() override {
        double rand = random->GetDouble();
        return rand > 0.85;
    }

    std::string GetColor() override {
        return "green";
    }
};