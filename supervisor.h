#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include "remotecontrol.h"
#include <string>
#include <vector>

class CSupervisor {
    public:
        CSupervisor(const std::string & name)
        : m_name(name)
        , m_selectedDrone (0) {
        }
        ~CSupervisor() {
            for (CRemoteControl * pRemote : m_remotes) {
                delete pRemote;
            }
        }

        void addRemote(CRemoteControl * pRemote) {
            m_remotes.push_back(pRemote);
        }

        CRemoteControl * getRemote() {
            if (m_selectedDrone >= m_remotes.size()) nullptr; 
            return m_remotes[m_selectedDrone];
        } 

        void droneForward() {
            if (m_selectedDrone >= m_remotes.size()) return; 
            m_remotes[m_selectedDrone]->goForward();
        }

        void droneBackward() {
            if (m_selectedDrone >= m_remotes.size()) return;
            m_remotes[m_selectedDrone]->goBackward();
        }

        void droneLeft() {
            if (m_selectedDrone >= m_remotes.size()) return;
            m_remotes[m_selectedDrone]->goLeft();
        }

        void droneRight() {
            if (m_selectedDrone >= m_remotes.size()) return;
            m_remotes[m_selectedDrone]->goRight();
        }

        void selectNext() {
            size_t size = m_remotes.size();
            if (size == 0) return;
            m_selectedDrone = (m_selectedDrone + 1) % size;
        }

        void selectPrev() {
            size_t size = m_remotes.size();
            if (size == 0) return;
            m_selectedDrone = (m_selectedDrone + size - 1) % size;
        }

        CRemoteControl * getSelectedDrone() const { 
            if (m_selectedDrone < m_remotes.size()) return m_remotes[m_selectedDrone]; 
            else return nullptr;
        } 

    private:
        std::string                   m_name;
        std::vector<CRemoteControl *> m_remotes;
        size_t                        m_selectedDrone;
};

#endif