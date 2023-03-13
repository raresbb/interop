#include <mutex>
#include "definitions.h"

namespace fzd_gui_interface {
    /*
    struct fzd_gui::vehicle_state glob_vehicle_state;
    std::mutex mx_glob_vehicle_state;
    */
    struct fzd_gui::dyn_state glob_dyn_stateFL;
    std::mutex mx_glob_dyn_stateFL;

    struct fzd_gui::dyn_state glob_dyn_stateFR;
    std::mutex mx_glob_dyn_stateFR;

    struct fzd_gui::dyn_state glob_dyn_stateRL;
    std::mutex mx_glob_dyn_stateRL;

    struct fzd_gui::dyn_state glob_dyn_stateRR;
    std::mutex mx_glob_dyn_stateRR;

    /*
    struct fzd_gui::output glob_output;
    std::mutex mx_glob_output;
    */
}