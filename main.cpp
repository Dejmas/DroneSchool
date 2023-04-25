#include <iostream>
#include "droneschool.h"
#include "userinterface.h"
using namespace std;

unsigned CDrone::lastId = 0;

int main(int argc, char *argv[])
{
    CDroneSchool droneSchool;
    droneSchool.createSupervisor("Dr. Drone Expert");
    droneSchool.addDrone("Drone 1", CCoord(500, 500));
    droneSchool.addDrone("Drone 2", CCoord(400, 500));
    droneSchool.addUser("User 1");
    droneSchool.addUser("User 2");
    // assign drones to users and all to supervisor
    droneSchool.distributeDrones();
    CUserInterface_SDL gui{droneSchool};
    if (!gui.init()) {
        std::cerr << "Some error" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }
    gui.animationLoop();

    return 0;
}
