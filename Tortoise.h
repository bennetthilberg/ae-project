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
        return rand > 0.8;
    }

    std::string GetColor() override {
        return "green";
    }

    virtual emp::Ptr<Organism> CheckReproduction() override {
        std::cout << "Checking reproduction (tortoise)" << std::endl;
        if (points > 100) {
            std::cout << "Reproducing (Tortoise)" << std::endl;
            emp::Ptr<Tortoise> offspring = new Tortoise(*this);
            offspring->SetPoints(0);
            points = 0;
            return offspring;
        }
        std::cout << "i'm a tortoise that can't reproduce" << std::endl;
        return nullptr;
    }
};