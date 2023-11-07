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
        std::cout << "# orgs: " << GetNumOrgs() << std::endl;
        emp::vector<size_t> processSchedule =
            emp::GetPermutation(random, GetSize());
        for (int i : processSchedule) {
            if (!pop[i] || !IsOccupied(i)) {
                continue;
            }

            // Check if there are neighboring orgs at the org's position
            //bool doesOrgHaveCompany = false;
            /*if (GetValidNeighborOrgIDs(i).size() > 0) {
                doesOrgHaveCompany = true;
            }*/
            pop[i]->Process(/*doesOrgHaveCompany*/);
            if(pop[i]->ShouldIMove()){
                MoveOrganism(i);
            }

        }

        emp::vector<size_t> movementSchedule =
            emp::GetPermutation(random, GetSize());
        for (int i : movementSchedule) {
            if (!pop[i] || !IsOccupied(i)) {
                continue;
            }
            if (pop[i]->ShouldIMove()) {
                MoveOrganism(i);
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
                DoBirth(*offspring, i);
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