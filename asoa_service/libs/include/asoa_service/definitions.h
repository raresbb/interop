#ifndef fzd_gui_DEFINITIONS_H
#define fzd_gui_DEFINITIONS_H


typedef struct taitime {
    uint64_t tai_seconds;
    uint32_t tai_nanoseconds;
} taitime;

namespace fzd_gui{

    static const char tagFR[] = "FR";
    static const char tagFL[] = "FL";
    static const char tagRR[] = "RR";
    static const char tagRL[] = "RL";

    template <typename T>
    void cartesian2Polar(T &x, T &y, T &r, T &theta) {
        r = sqrt(x*x + y*y);
        theta = atan2(y,x);
    }

    template <typename T>
    void polar2Cartesian(T &r, T &theta, T &x, T &y) {
        x = r * cos(theta);
        y = r * sin(theta);
    }

    template <typename T>
    void enu_to_vehicle_frame(T &east, T &north, T &yaw, T &x, T &y) {
        float mag, angle, yaw_delta;
        fzd_gui::cartesian2Polar(east, north, mag, angle);
        yaw_delta = angle - yaw;
        fzd_gui::polar2Cartesian(mag, yaw_delta, x, y);
    }

    struct dyn_state {
        double wheel_angle_deg;
        double rotation_speed_rad_s;
        taitime time;
    };

}

#endif
