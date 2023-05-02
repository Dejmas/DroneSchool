#include <iostream>
#include <memory>
#include "staticitem.h"
#include "droneschool.h"
#include "drone.h"
#include "userinterface.h"
#include "lesson.h"
#include "reachdestinationcommand.h"
#include "pickitemcommand.h"
#include "dropitemcommand.h"
using namespace std;

unsigned IItem::lastId = 0;

ALesson makeLesson() {
    ALesson lesson = make_shared<CLesson> ("From A to B");
    
    auto startPort = std::make_shared<CStaticItem>("port", "helipad");
    startPort->setPosition(CCoord(200, 650));
    startPort->setWidth(150);
    startPort->setHeight(150);

    

    auto spot1 = std::make_shared<CStaticItem>("spot-1", "spot-1");
    spot1->setWidth(100);
    spot1->setHeight(100);
    spot1->setPosition(CCoord(200, 150));

    auto spot2 = std::make_shared<CStaticItem>("spot-2", "spot-2");
    spot2->setWidth(100);
    spot2->setHeight(100);
    spot2->setPosition(CCoord(300, 430));

    auto spot3 = std::make_shared<CStaticItem>("spot-3", "spot-3");
    spot3->setWidth(100);
    spot3->setHeight(100);
    spot3->setPosition(CCoord(880, 320));

    auto rod = std::make_shared<CStaticItem>("rod", "rod");
    rod->setPosition(spot1->getPosition());
    rod->setIsPickable(true);

    auto fish = std::make_shared<CStaticItem>("fish", "fish");
    fish->setPosition(spot3->getPosition());
    fish->setIsPickable(true);

    lesson->setStartLocation(startPort->getPosition());
    lesson->addItem(startPort);
    lesson->addItem(spot1);
    lesson->addItem(spot2);
    lesson->addItem(spot3);
    lesson->addItem(rod);
    lesson->addItem(fish);
    lesson->addCommand(make_shared<CReachDestinationCommand> (spot1->getPosition()));
    lesson->addCommand(make_shared<CPickItemCommand> (rod));
    lesson->addCommand(make_shared<CReachDestinationCommand> (spot2->getPosition()));
    lesson->addCommand(make_shared<CDropItemCommand> (rod));
    lesson->addCommand(make_shared<CReachDestinationCommand> (spot3->getPosition()));
    lesson->addCommand(make_shared<CPickItemCommand> (fish));
    lesson->addCommand(make_shared<CReachDestinationCommand> (startPort->getPosition()));
    lesson->addCommand(make_shared<CDropItemCommand> (fish));


    return lesson;
}

int main(int argc, char *argv[])
{
    CDroneSchool droneSchool;
    droneSchool.setupDrone("Drone 1", CCoord(500, 500));
    droneSchool.setupSupervisor("Dr. Drone Expert");
    droneSchool.setupStudent("Student 1");

    ALesson lesson = makeLesson();

    droneSchool.addLesson(lesson);
    droneSchool.startLesson();

    // assign drones to users and all to supervisor
    CUserInterface_SDL gui{droneSchool};

    if (!gui.init()) {
        std::cerr << "Some error" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    gui.registerTexture("drone", "resources/drone.png");
    gui.registerTexture("rod", "resources/rod.png");
    gui.registerTexture("fish", "resources/fish.png");
    gui.registerTexture("helipad", "resources/helipad.png");
    gui.registerTexture("helipad-2", "resources/helipad-2.png");
    gui.registerTexture("spot-1", "resources/spot-1.png");
    gui.registerTexture("spot-2", "resources/spot-2.png");
    gui.registerTexture("spot-3", "resources/spot-3.png");

    gui.animationLoop();

    return 0;
}
