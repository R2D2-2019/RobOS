#include <../headers/battery_frame_action.hpp>

namespace r2d2::robos {
    battery_frame_action_c::battery_frame_action_c(base_comm_c &comm, actions_t &actions)
        : frame_action_c(comm, frame_type::BATTERY_LEVEL, actions) {
    }

    void battery_frame_action_c::process_packet(frame_s &frame) {
        auto battery_frame =
            frame.as_frame_type<frame_type::BATTERY_LEVEL>();
            if (battery_percentage != battery_frame.percentage) {
                changed = true;
                battery_percentage = battery_frame.percentage;
            }
            // Data recieved, reset timer
            mark_received();
    }

    void battery_frame_action_c::reply_to_data() {
        if (changed) {
            frame_display_8x8_character_s frame = {0};
            frame.x = 0;
            frame.y = 0;
            frame.red = 0xFF;
            frame.green = 0xFF;
            frame.blue = 0xFF;

            for (unsigned int i = 0; i < 9; i++) {
                frame.characters[i] = battery_message[i];
            }
            int_to_str(battery_percentage, frame.characters + 9, 10);

            comm.send(frame);
            
            changed = false;
        }
    }
} // namespace r2d2::robos