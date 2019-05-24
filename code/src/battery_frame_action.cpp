#include <battery_frame_action.hpp>

namespace r2d2::robos {
    battery_frame_action_c::battery_frame_action_c(base_comm_c &comm,
                                                   frame_s &frame)
        : frame_action_c(comm, frame),
          ostream(comm, claimed_display_cursor::ROBOS_POWER_CURSOR, {0, 255, 0},
                  0, 0) {
    }

    void battery_frame_action_c::red_cursor() {
        ostream.set_color({255, 0, 0});
    }
    void battery_frame_action_c::green_cursor() {
        ostream.set_color({0, 255, 0});
    }

    void battery_frame_action_c::reply_to_data() {
        if (!changed) {
            return;
        }

        // If battery percentage is under the 30 percent, make the text red
        // Else make the text green
        if (last_frame.percentage < 30) {
            red_cursor();
        } else {
            green_cursor();
        }

        ostream << battery_message << last_frame.percentage << hwlib::flush;

        changed = false;
    }
} // namespace r2d2::robos