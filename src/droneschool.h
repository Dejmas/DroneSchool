#ifndef DRONESCHOOL_H
#define DRONESCHOOL_H

#include "drone.h"
#include "user.h"
#include "supervisor.h"
#include "remotecontrol.h"

#include <vector>

class CDroneSchool {
    public:
        CDroneSchool (): m_supervisor(nullptr) {
        }
        // delete CC and OP =
        CDroneSchool (const CDroneSchool &) = delete;
        CDroneSchool & operator = (const CDroneSchool &) = delete;

        ~CDroneSchool() {
            for (CDrone * pDrone : m_drones) { 
                delete pDrone;
            }
            for (CUser * pUser : m_users) {
                delete pUser;
            }
            delete m_supervisor;
        }

        void addDrone (const std::string & name, CCoord coord = CCoord()) {
            auto drone = new CDrone(name, coord);
            m_drones.push_back(drone);
        }

        void createSupervisor (const std::string & name) {
            auto sv = new CSupervisor(name);
            m_supervisor = sv;
        }

        void addUser (const std::string & name) {
            auto user = new CUser(name);
            m_users.push_back(user);
        }

        void distributeDrones() {
            size_t noPairs = std::min(m_drones.size(), m_users.size());
            for (size_t i = 0; i < noPairs; i ++) {
                CRemoteControl * remote = new CRemoteControl(*m_drones[i]);
                m_users[i]->setRemote(remote);
                m_supervisor->addRemote(remote);
            }
        }

        void updateDrones() {
            for (auto pDrone : m_drones) {
                pDrone->update();
            }
        }

        // can't be const, it's returning owning non-const pointer
        auto getSupervisor() { return m_supervisor; } 

        const std::vector<CDrone *> & getDrones() const {
            return m_drones;
        }

    private:
        std::vector<CDrone *> m_drones;
        std::vector<CUser *> m_users;
        CSupervisor *       m_supervisor;
};

#endif // DRONESCHOOL_H