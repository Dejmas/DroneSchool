#include <iostream>
#include <memory>
#include "staticitem.h"
#include "droneschool.h"
#include "drone.h"
#include "userinterfacesdl.h"
#include "lesson.h"
#include "reachdestinationcommand.h"
#include "pickitemcommand.h"
#include "dropitemcommand.h"

ALesson makeLesson() {
    ALesson lesson = std::make_shared<CLesson> ("From A to B");

    auto background = std::make_shared<CStaticItem>("lawn", "lawn-2");
    background->setWidth(1200);
    background->setHeight(800);
    background->setPosition(CCoord(background->getWidth()/2, background->getHeight()/2));
    
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
    rod->setWidth(100);
    rod->setHeight(100);

    auto fish = std::make_shared<CStaticItem>("fish", "fish");
    fish->setPosition(spot3->getPosition());
    fish->setIsPickable(true);

    lesson->setStartLocation(startPort->getPosition());
    lesson->addItem(background);
    lesson->addItem(startPort);
    lesson->addItem(spot1);
    lesson->addItem(spot2);
    lesson->addItem(spot3);
    lesson->addItem(rod);
    lesson->addItem(fish);
    lesson->addCommand(std::make_shared<CReachDestinationCommand> (spot1->getPosition()));
    lesson->addCommand(std::make_shared<CPickItemCommand> (rod));
    lesson->addCommand(std::make_shared<CReachDestinationCommand> (spot2->getPosition()));
    lesson->addCommand(std::make_shared<CDropItemCommand> (rod));
    lesson->addCommand(std::make_shared<CReachDestinationCommand> (spot3->getPosition()));
    lesson->addCommand(std::make_shared<CPickItemCommand> (fish));
    lesson->addCommand(std::make_shared<CReachDestinationCommand> (startPort->getPosition()));
    lesson->addCommand(std::make_shared<CDropItemCommand> (fish));


    return lesson;
}

int main(int argc, char *argv[])
{
    CDroneSchool droneSchool;
    CUserInterface_SDL gui{droneSchool};

    droneSchool.setupDrone("Drone 1", CCoord(500, 500));
    droneSchool.setupSupervisor("Dr. Drone Expert");
    droneSchool.setupStudent("Student 1", gui);
    //droneSchool.setBackground("lawn");

    ALesson lesson = makeLesson();

    droneSchool.addLesson(lesson);
    droneSchool.startLesson();
   

    if (!gui.init()) {
        std::cerr << "Some error" << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    gui.registerTexture("drone", "resources/drone-light.png");
    gui.registerTexture("rod", "resources/rod.png");
    gui.registerTexture("fish", "resources/fish.png");
    gui.registerTexture("helipad", "resources/helipad.png");
    gui.registerTexture("helipad-2", "resources/helipad-2.png");
    gui.registerTexture("spot-1", "resources/spot-1.png");
    gui.registerTexture("spot-2", "resources/spot-2.png");
    gui.registerTexture("spot-3", "resources/spot-3.png");
    gui.registerTexture("lawn", "resources/lawn.jpeg");
    gui.registerTexture("lawn-2", "resources/lawn-2.jpeg");
    // gui.registerTexture("light", "resources/light.png");

    gui.animationLoop();

    return 0;
}
