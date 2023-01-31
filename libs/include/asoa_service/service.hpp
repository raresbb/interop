#include <cstdio>
#include "definitions.h"
#include "ext_interface.h"
#include "include/asoa_service/interface/guarantees/CarControlCommands.hpp"
#include "include/asoa_service/interface/requirements/state4ftr.hpp"
#include "include/asoa_service/interface/requirements/dyn_state.hpp"

// Read current time. This is currently realized by receiving the time information via ethernet.
// In the future ASOA will have a built in function for that.
void read_taitime(taitime &taitime) {
    /* ASOA time API */
    asoa::OS::time::time_t ts;
    //ts = asoa::OS::time::getTime(); //Todo: Readd this lines when ASOA uses clock_tai

    // Todo: Delete the four next lines when ASOA uses clock_tai
    struct timespec tspec{};
    clock_gettime(CLOCK_TAI, &tspec);
    ts.tv_sec = tspec.tv_sec;
    ts.tv_nsec = tspec.tv_nsec;

    //Write results in taitime struct
    taitime.tai_seconds = ts.tv_sec;
    taitime.tai_nanoseconds = ts.tv_nsec;
}

class FZDGUIService : public Service {
public:

    // Requirements
    /* 
    class : public Requirement<state4ftr, 5> {
        bool parameterFilter(const state4ftr::Parameter *param) { return true; }
    } requirement_state4ftr;
    */
    class : public Requirement<dyn_state, 5, fzd_gui::tagFL> {
        bool parameterFilter(const dyn_state::Parameter *param) { return true; }
    } requirement_dynstateFL;
    class : public Requirement<dyn_state, 5, fzd_gui::tagFR> {
        bool parameterFilter(const dyn_state::Parameter *param) { return true; }
    } requirement_dynstateFR;
    class : public Requirement<dyn_state, 5, fzd_gui::tagRL> {
        bool parameterFilter(const dyn_state::Parameter *param) { return true; }
    } requirement_dynstateRL;
    class : public Requirement<dyn_state, 5, fzd_gui::tagRR> {
        bool parameterFilter(const dyn_state::Parameter *param) { return true; }
    } requirement_dynstateRR;


    // Guarantees
    /*
    static class : public Guarantee<CarControlCommands> {
    } guarantee_ctrlcom;
    */
   /*
    class FZDGUI_Calc : public PeriodicTask {
    private:
        CarControlCommands::Data data_ctrl_com{};
        fzd_gui::output ext_control_output{};

        void write_data() {
            taitime current_time{};
            read_taitime(current_time);

            // If time information is not available, comment in to copy time from state4ftr
//            fzd_gui::vehicle_state state{};
//            fzd_gui_interface::rx_vehicle_state(state);
//            current_time.tai_seconds = state.time.tai_seconds;
//            current_time.tai_nanoseconds = state.time.tai_nanoseconds;

            data_ctrl_com.tai_seconds = current_time.tai_seconds;
            data_ctrl_com.tai_nanoseconds = current_time.tai_nanoseconds;
            data_ctrl_com.frame_counter++;

            data_ctrl_com.target_vel_x = ext_control_output.velocity;
            data_ctrl_com.target_curvature = ext_control_output.curvature;
            data_ctrl_com.target_cor_x = ext_control_output.center_of_rotation_x;
            data_ctrl_com.emergency_stop = ext_control_output.em_brake_request;
        }

        void send_data() {
            guarantee_ctrlcom.sendData(data_ctrl_com);
        }

    public:
        void onWork() {
            // Read control output from global variable written by python control thread
            fzd_gui_interface::rx_output(ext_control_output);

            // Publish data to ASOA
            write_data();
            send_data();
        }
    } fzd_gui_calc;
    */
   /*
    class : public ConditionalTask {
    public:

        Requirement<state4ftr>::AccessHandle *access_handle;

        void onWork() {

            // Pull data from requirements
            state4ftr::Data data;
            if (access_handle->pullData(data)) {

                fzd_gui::vehicle_state ext_vehicle_state{};

                ext_vehicle_state.time.tai_seconds = data.tai_seconds;
                ext_vehicle_state.time.tai_nanoseconds = data.tai_nanoseconds;

                // Convert ENU to vehicle body coordniates for the velocity
                float vel_x, vel_y, acc_x, acc_y;
                fzd_gui::enu_to_vehicle_frame(data.vel_enu_m_s[0], data.vel_enu_m_s[1], data.rpy_rad[2], vel_x, vel_y);
                ext_vehicle_state.vel_x_m_s = vel_x;
                fzd_gui::enu_to_vehicle_frame(data.acc_enu_m_s2[0], data.acc_enu_m_s2[1], data.rpy_rad[2], acc_x, acc_y);
                ext_vehicle_state.acc_x_m_s2 = acc_x;
                ext_vehicle_state.acc_y_m_s2 = acc_y;

                fzd_gui_interface::tx_vehicle_state(ext_vehicle_state);

            }
        }
    } cond_task_state4ftr;
    */
    class : public ConditionalTask {
    public:

        Requirement<dyn_state, 5, fzd_gui::tagFL>::AccessHandle *access_handle;

        void onWork() {

            // Pull data from requirements
            dyn_state::Data data;
            if (access_handle->pullData(data)) {

                fzd_gui::dyn_state ext_dyn_state{};

                ext_dyn_state.time.tai_seconds = data.tai_seconds;
                ext_dyn_state.time.tai_nanoseconds = data.tai_nanoseconds;
                ext_dyn_state.wheel_angle_deg = float(data.steering_angle_rad / (2 * M_PI) * 360);
                ext_dyn_state.rotation_speed_rad_s = data.drive_speed_rad_s;

                fzd_gui_interface::tx_dyn_stateFL(ext_dyn_state);

            }
        }
    } cond_task_dynstateFL;

    class : public ConditionalTask {
    public:

        Requirement<dyn_state, 5, fzd_gui::tagFR>::AccessHandle *access_handle;

        void onWork() {

            // Pull data from requirements
            dyn_state::Data data;
            if (access_handle->pullData(data)) {

                fzd_gui::dyn_state ext_dyn_state{};

                ext_dyn_state.time.tai_seconds = data.tai_seconds;
                ext_dyn_state.time.tai_nanoseconds = data.tai_nanoseconds;
                ext_dyn_state.wheel_angle_deg = float(data.steering_angle_rad / (2 * M_PI) * 360);
                ext_dyn_state.rotation_speed_rad_s = data.drive_speed_rad_s;

                fzd_gui_interface::tx_dyn_stateFR(ext_dyn_state);

            }
        }
    } cond_task_dynstateFR;

    class : public ConditionalTask {
    public:

        Requirement<dyn_state, 5, fzd_gui::tagRL>::AccessHandle *access_handle;

        void onWork() {

            // Pull data from requirements
            dyn_state::Data data;
            if (access_handle->pullData(data)) {

                fzd_gui::dyn_state ext_dyn_state{};

                ext_dyn_state.time.tai_seconds = data.tai_seconds;
                ext_dyn_state.time.tai_nanoseconds = data.tai_nanoseconds;
                ext_dyn_state.wheel_angle_deg = float(data.steering_angle_rad / (2 * M_PI) * 360);
                ext_dyn_state.rotation_speed_rad_s = data.drive_speed_rad_s;

                fzd_gui_interface::tx_dyn_stateRL(ext_dyn_state);

            }
        }
    } cond_task_dynstateRL;

    class : public ConditionalTask {
    public:

        Requirement<dyn_state, 5, fzd_gui::tagRR>::AccessHandle *access_handle;

        void onWork() {

            // Pull data from requirements
            dyn_state::Data data;
            if (access_handle->pullData(data)) {

                fzd_gui::dyn_state ext_dyn_state{};

                ext_dyn_state.time.tai_seconds = data.tai_seconds;
                ext_dyn_state.time.tai_nanoseconds = data.tai_nanoseconds;
                ext_dyn_state.wheel_angle_deg = float(data.steering_angle_rad / (2 * M_PI) * 360);
                ext_dyn_state.rotation_speed_rad_s = data.drive_speed_rad_s;

                fzd_gui_interface::tx_dyn_stateRR(ext_dyn_state);

            }
        }
    } cond_task_dynstateRR;


    FZDGUIService(const char *name, double ptask_freq_hz) : Service(name) {
        // Add requirements
        //addRequirement(&requirement_state4ftr);
        addRequirement(&requirement_dynstateFL);
        addRequirement(&requirement_dynstateFR);
        addRequirement(&requirement_dynstateRL);
        addRequirement(&requirement_dynstateRR);

        // Add guarantees
        //addGuarantee(&guarantee_ctrlcom);

        // Add tasks
        /*
        PeriodicTask::PeriodicTaskParam_t ptask_param;
        ptask_param.frequencyHz = ptask_freq_hz;
        ptask_param.start_ref = asoa::OS::time::getTime();
        initializeTask(&fzd_gui_calc, ptask_param);
        */
        ConditionalTask::ConditionalTaskParam_t ctask_param;
        /*
        initializeTask(&cond_task_state4ftr, ctask_param);
        taskReadsFromRequirement(cond_task_state4ftr, requirement_state4ftr, &cond_task_state4ftr.access_handle);
        taskAddDataTrigger(cond_task_state4ftr, requirement_state4ftr, cond_task_state4ftr.access_handle);
        */
        initializeTask(&cond_task_dynstateFL, ctask_param);
        taskReadsFromRequirement(cond_task_dynstateFL, requirement_dynstateFL, &cond_task_dynstateFL.access_handle);
        taskAddDataTrigger(cond_task_dynstateFL, requirement_dynstateFL, cond_task_dynstateFL.access_handle);

        initializeTask(&cond_task_dynstateFR, ctask_param);
        taskReadsFromRequirement(cond_task_dynstateFR, requirement_dynstateFR, &cond_task_dynstateFR.access_handle);
        taskAddDataTrigger(cond_task_dynstateFR, requirement_dynstateFR, cond_task_dynstateFR.access_handle);

        initializeTask(&cond_task_dynstateRL, ctask_param);
        taskReadsFromRequirement(cond_task_dynstateRL, requirement_dynstateRL, &cond_task_dynstateRL.access_handle);
        taskAddDataTrigger(cond_task_dynstateRL, requirement_dynstateRL, cond_task_dynstateRL.access_handle);

        initializeTask(&cond_task_dynstateRR, ctask_param);
        taskReadsFromRequirement(cond_task_dynstateRR, requirement_dynstateRR, &cond_task_dynstateRR.access_handle);
        taskAddDataTrigger(cond_task_dynstateRR, requirement_dynstateRR, cond_task_dynstateRR.access_handle);

    }

    ~FZDGUIService() = default;

    bool onStartRequest() {
        std::cout << "FZDGUI service is being started." << std::endl;
        return true;
    }

    bool onPrepareRequest() {
        return true;
    }

    bool onStopRequest() {
        std::cout << "FZDGUI service is being stopped." << std::endl;
        return true;
    }

    std::string name();

};

// Instantiating of guarantees
//decltype(FZDGUIService::guarantee_ctrlcom) FZDGUIService::guarantee_ctrlcom;
