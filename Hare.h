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
        return rand > 0.3;
    }

    std::string GetColor() override {
        return "blue";
    }
    virtual emp::Ptr<Organism> CheckReproduction() override {
        std::cout << "Checking reproduction (hare)" << std::endl;
        if (points > 100) {
            std::cout << "Reproducing (Hare)" << std::endl;
            emp::Ptr<Hare> offspring = new Hare(*this);
            offspring->SetPoints(0);
            points = 0;
            return offspring;
        }
        std::cout << "i'm a hare that can't reproduce" << std::endl;
        return nullptr;
    }
};