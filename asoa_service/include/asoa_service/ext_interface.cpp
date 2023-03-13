#include "ext_interface.h"

namespace fzd_gui_interface {
    /*
    void tx_vehicle_state(fzd_gui::vehicle_state ext_vehicle_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_state{mx_glob_vehicle_state};
        glob_vehicle_state = ext_vehicle_state;
    }

    void rx_vehicle_state(fzd_gui::vehicle_state &ext_vehicle_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_vehicle_state{mx_glob_vehicle_state};
        ext_vehicle_state = glob_vehicle_state;
    }
    */
    void tx_dyn_stateFL(fzd_gui::dyn_state ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_dynstateFL{mx_glob_dyn_stateFL};
        glob_dyn_stateFL = ext_dyn_state;
    }

    void rx_dyn_stateFL(fzd_gui::dyn_state &ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_dynstateFL{mx_glob_dyn_stateFL};
        ext_dyn_state = glob_dyn_stateFL;
    }

    void tx_dyn_stateFR(fzd_gui::dyn_state ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_dynstateFR{mx_glob_dyn_stateFR};
        glob_dyn_stateFR = ext_dyn_state;
    }

    void rx_dyn_stateFR(fzd_gui::dyn_state &ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_dynstateFR{mx_glob_dyn_stateFR};
        ext_dyn_state = glob_dyn_stateFR;
    }

    void tx_dyn_stateRL(fzd_gui::dyn_state ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_dynstateRL{mx_glob_dyn_stateRL};
        glob_dyn_stateRL = ext_dyn_state;
    }

    void rx_dyn_stateRL(fzd_gui::dyn_state &ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_dynstateRL{mx_glob_dyn_stateRL};
        ext_dyn_state = glob_dyn_stateRL;
    }

    void tx_dyn_stateRR(fzd_gui::dyn_state ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_dynstateRR{mx_glob_dyn_stateRR};
        glob_dyn_stateRR = ext_dyn_state;
    }

    void rx_dyn_stateRR(fzd_gui::dyn_state &ext_dyn_state) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_dynstateRR{mx_glob_dyn_stateRR};
        ext_dyn_state = glob_dyn_stateRR;
    }
    /*
    void tx_output(fzd_gui::output ext_output) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> guard_glob_output{mx_glob_output};
        glob_output = ext_output;
    }

    void rx_output(fzd_gui::output &ext_output) {
        //Use lock_guard to lock ext variable
        std::lock_guard<std::mutex> lk_glob_output{mx_glob_output};
        ext_output = glob_output;
    }
    */
}