#ifndef DRONESCHOOL_H
#define DRONESCHOOL_H

#include "drone.h"
#include "user.h"
#include "student.h"
#include "supervisor.h"
#include "remotecontrol.h"
#include "lesson.h"

#include <vector>
#include <algorithm>

class CDroneSchool {
public:
    CDroneSchool (): m_supervisor(nullptr) {
    }
    // delete CC and OP =
    CDroneSchool (const CDroneSchool &) = delete;
    CDroneSchool & operator = (const CDroneSchool &) = delete;

    ~CDroneSchool() {
        delete m_drone;
        delete m_student;
        delete m_supervisor;
    }

    void setupDrone (const std::string & name, CCoord coord = CCoord()) {
        auto drone = new CDrone(*this, name, "drone", coord);
        m_drone = drone;
    }

    void setupSupervisor (const std::string & name) {
        m_supervisor = new CSupervisor(name);
        m_supervisor->setRemote(m_drone->getRemoteControl());
    }

    void setupStudent (const std::string & name) {
        m_student = new CStudent(name);
        m_student->setRemote(m_drone->getRemoteControl());
    }

    void addLesson(ALesson lesson) {
        m_lessons.push_back(lesson);
        m_currentLesson = lesson;
    }

    void setUserActions(TUserInputAction userActions) {
        m_userActions = userActions;
        m_student->setUserActions(userActions);
    }

    auto getItems() const {
        return m_currentLesson->getItems();
    }

    auto getItemsNear(CCoord position, double distance) {
        std::vector<AItem> res;
        for (auto item : getItems()) {
            if ((item->getPosition() - position).abs() < distance) {
                res.push_back(item);
            }
        }
        std::sort(res.begin(), res.end(), [&position](AItem itemA, AItem itemB) {
            return (itemA->getPosition() - position).abs() < (itemB->getPosition() - position).abs();
        });
        return res;
    }

    void startLesson() {
        m_currentLesson->start(m_supervisor, m_drone);
    }

    void update() {
        m_drone->update();
        if (!m_currentLesson->isComplete()) {
            m_currentLesson->update();
        } else {
            m_currentLesson->start(m_student, m_drone);
        }
    }

    // can't be const, it's returning owning non-const pointer
    auto getSupervisor() { return m_supervisor; }

    const CDrone * getDrone() const { return m_drone; }

private:
    CDrone      *         m_drone;
    CSupervisor *         m_supervisor;
    CStudent    *         m_student;
    std::vector<ALesson>  m_lessons;
    ALesson               m_currentLesson;
    TUserInputAction      m_userActions;

};

#endif // DRONESCHOOL_H