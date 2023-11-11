#ifndef WORLD_H
#define WORLD_H
#include "Org.h"
#include "emp/Evolve/World.hpp"
#include "emp/math/Random.hpp"
#include "emp/math/random_utils.hpp"

class OrgWorld : public emp::World<Organism> {
    emp::Random& random;
    emp::Ptr<emp::Random> random_ptr;

  public:
    OrgWorld(emp::Random& _random)
        : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

    void Update() {
        emp::World<Organism>::Update();

        std::cout << "# orgs at beginning of update: " << GetNumOrgs() << std::endl;
        emp::vector<size_t> processSchedule =
            emp::GetPermutation(random, GetSize());
        for (int i : processSchedule) {
            if (!pop[i] || !IsOccupied(i)) {
                continue;
            }
            pop[i]->Process();
            /*if(pop[i]->ShouldIMove()){
                MoveOrganism(i);
            }*/
        }

        emp::vector<size_t> movementSchedule =
            emp::GetPermutation(random, GetSize());
        for (int i : movementSchedule) {
            if (!pop[i] || !IsOccupied(i)) {
                continue;
            }
            if (pop[i]->ShouldIMove()) {
                std::cout << "I should move! Running MoveOrg" << std::endl;
                MoveOrganism(i);
            }
            else{
                std::cout << "I should not move" << std::endl;
            }
        }

        emp::vector<size_t> reproductionSchedule =
            emp::GetPermutation(random, GetSize());
        for (int i : reproductionSchedule) {
            if (!pop[i] || !IsOccupied(i)) {
                continue;
            }
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring) {
                // DoBirth(*offspring, i);
                std::cout << "Offspring is truthy! Finding a place to put offspring..." << std::endl;
                emp::WorldPosition possibleOffspringLocation =
                    GetRandomNeighborPos(i);
                if (IsOccupied(possibleOffspringLocation/*.GetIndex()*/)) {
                    std::cout << "First random offspring spot was occupied, looping to try and find others." << std::endl;
                    for (int h = 0;
                         h < 10 &&
                         IsOccupied(possibleOffspringLocation/*.GetIndex()*/);
                         h++) {
                        possibleOffspringLocation = GetRandomNeighborPos(i);
                    }
                }
                if(!IsOccupied(possibleOffspringLocation/*.GetIndex()*/)){
                    std::cout << "Open spot! Adding org (reproduction)" << std::endl;
                    AddOrgAt(offspring, possibleOffspringLocation);
                } else {
                    std::cout << "No room for offspring" << std::endl;
                }
                /*
                //while (IsOccupied(possibleOffspringLocation.GetIndex())) {
                    //possibleOffspringLocation = GetRandomNeighborPos(i);
                }
                */
                //AddOrgAt(offspring, possibleOffspringLocation);
            }
        }

        std::cout << "Update done" << std::endl;
    }
    emp::Ptr<Organism> ExtractOrganism(int i) {
        emp::Ptr<Organism> orgPtr = pop[i];
        pop[i] = nullptr;
        return orgPtr;
    }
    void MoveOrganism(int i) {
        emp::Ptr<Organism> orgPtr = ExtractOrganism(i);
        emp::WorldPosition newPos = GetRandomNeighborPos(i);
        while (IsOccupied(newPos.GetIndex())) {
            newPos = GetRandomNeighborPos(i);
        }
        AddOrgAt(orgPtr, newPos);
    }
};
#endif