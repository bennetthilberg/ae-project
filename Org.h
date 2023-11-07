#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"
#include <random>

class Organism {
  private:
    double points;
    

  protected:
    std::string species;
    emp::Ptr<emp::Random> random;

  public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : random(_random), points(_points) {
        ;
    }
    virtual ~Organism() {
    }
    void SetPoints(double _in) {
        points = _in;
    }
    void AddPoints(double _in) {
        points += _in;
    }
    std::string GetSpecies() {
        return species;
    }
    virtual std::string GetColor(){
        return "black";
    }
    virtual void Process(/*bool doIHaveCompany*/) {
        std::cout << "Processing" << std::endl;
        //if (!doIHaveCompany) {
        //    points += 50;
        //}
    }
    virtual bool ShouldIMove() {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        double rand = distribution(generator);
        std::cout << "This is the default Org ShouldIMove! This should probably not be running!!!" << std::endl;
        if(rand > 0.5){
            return true;
        } else{
            return false;
        }
    }
    virtual emp::Ptr<Organism> CheckReproduction() {
        std::cout << "Checking reproduction" << std::endl;
        if (points > 1000) {
            std::cout << "Reproducing" << std::endl;
            emp::Ptr<Organism> offspring = new Organism(*this);
            offspring->SetPoints(0);
            points = 0;
            return offspring;
        }
        return nullptr;
    }
};
#endif