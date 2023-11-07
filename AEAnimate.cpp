#include "Hare.h"
#include "Org.h"
#include "Tortoise.h"
#include "World.h"
#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include <vector>

emp::web::Document doc{"target"};

class AEAnimator : public emp::web::Animate {

    // arena width and height
    const int num_h_boxes = 50;
    const int num_w_boxes = 50;
    const double RECT_SIDE = 10;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};

    emp::web::Canvas canvas{width, height, "canvas"};
    emp::Random random{5};
    OrgWorld world{random};

  public:
    AEAnimator() {
        // shove canvas into the div
        // along with a control button
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
        // Organism* new_org0 = new Organism(&random, 0, 0);
        // world.Inject(*new_org0);
        Tortoise* firstTortoise = new Tortoise(&random, 0);
        Hare* firstHare = new Hare(&random, 0);
        /*world.Inject(*firstTortoise);
        world.Inject(*firstHare);*/
        //world.Inject(emp::NewPtr<Tortoise>(&random, 0));
        //world.Inject(emp::NewPtr<Hare>(&random, 0));
        world.AddOrgAt(firstTortoise, 0);
        world.AddOrgAt(firstHare, 20);

        world.Resize(50, 50);
    }

    void DoFrame() override {
        canvas.Clear();
        world.Update();
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    // Organism org = world.GetOrg(org_num);
                    // emp::Ptr<Organism> orgPtr = world.GetOrgPtr(org_num);
                    emp::Ptr<Organism> orgPtr = world.GetOrgPtr(org_num);

                    // std::string speciesColor =
                    // speciesColors[org.GetSpecies()];

                    // Debugging: Output the species and color to the console
                    /*std::cout << "Species: " << orgPtr->GetSpecies()
                              << ", Color: " << orgPtr->GetColor() << std::endl;*/

                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE,
                                RECT_SIDE, orgPtr->GetColor(), "black");
                } else {
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE,
                                RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }
};

AEAnimator animator;

int main() {

    animator.Step();
}