#include "lesson.h"
#include "drone.h"

CLesson::CLesson(const std::string & name) 
: m_name (name)
, m_isComplete (false)
, m_user (nullptr)
, m_drone (nullptr)
{
    
}

void CLesson::addCommand (ACommand command) {
    m_commands.push_back(command);
}

void CLesson::addItem (AItem item) {
    m_items.push_back(item);
}

void CLesson::setStartLocation(CCoord coord) {
    m_startLocation = coord;
}

void CLesson::start(IUser * user, CDrone * drone) {
    m_user = user;
    m_drone = drone;
    m_isComplete = false;
    m_commandIter = m_commands.begin();
    m_drone->setPosition(m_startLocation);
}

void CLesson::update() {
    if (m_commandIter == m_commands.end()) {
        m_isComplete = true;
        return;
    }
    ACommand command = *m_commandIter;
    if (command->isDone(*m_drone)) {
        std::printf("Done!\n");
        m_commandIter ++;
    } else {
        command->letUserWorkOnIt(m_user);
    }
}

bool CLesson::isComplete() const {
    return m_isComplete;
}