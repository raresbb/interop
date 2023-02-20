#include <mutex>
#include "definitions.h"

namespace fzd_gui_interface {
    /*
    extern struct fzd_gui::vehicle_state glob_vehicle_state;
    extern std::mutex mx_glob_vehicle_state;
    */
    extern struct fzd_gui::dyn_state glob_dyn_stateFL;
    extern std::mutex mx_glob_dyn_stateFL;

    extern struct fzd_gui::dyn_state glob_dyn_stateFR;
    extern std::mutex mx_glob_dyn_stateFR;

    extern struct fzd_gui::dyn_state glob_dyn_stateRL;
    extern std::mutex mx_glob_dyn_stateRL;

    extern struct fzd_gui::dyn_state glob_dyn_stateRR;
    extern std::mutex mx_glob_dyn_stateRR;
    /*
    extern struct fzd_gui::output glob_output;
    extern std::mutex mx_glob_output;
    */
    /*
    void tx_vehicle_state(fzd_gui::vehicle_state ext_vehicle_state);
    void rx_vehicle_state(fzd_gui::vehicle_state &ext_vehicle_state);
    */
    void tx_dyn_stateFL(fzd_gui::dyn_state ext_dyn_state);
    void rx_dyn_stateFL(fzd_gui::dyn_state &ext_dyn_state);
    void tx_dyn_stateFR(fzd_gui::dyn_state ext_dyn_state);
    void rx_dyn_stateFR(fzd_gui::dyn_state &ext_dyn_state);
    void tx_dyn_stateRL(fzd_gui::dyn_state ext_dyn_state);
    void rx_dyn_stateRL(fzd_gui::dyn_state &ext_dyn_state);
    void tx_dyn_stateRR(fzd_gui::dyn_state ext_dyn_state);
    void rx_dyn_stateRR(fzd_gui::dyn_state &ext_dyn_state);
    /*
    void tx_output(fzd_gui::output ext_output);
    void rx_output(fzd_gui::output &ext_output);
    */

}