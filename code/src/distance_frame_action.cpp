#include <../headers/distance_frame_action.hpp>

namespace r2d2::robos {
    distance_frame_action_c::distance_frame_action_c(base_comm_c &comm, actions_t &actions)
        : frame_action_c(comm, frame_type::DISTANCE, actions) {
    }

    void distance_frame_action_c::process_packet(frame_s &frame) {
        auto distance_frame = frame.as_frame_type<frame_type::DISTANCE>();

        if (distance_mm != distance_frame.mm) {
            changed = true;
            distance_mm = distance_frame.mm;
        }

        // Data recieved, reset timer
        mark_received();
    }

    void distance_frame_action_c::reply_to_data() {
        if (changed) {
            frame_display_8x8_character_s frame = {0};
            frame.x = 0;
            frame.y = 2;
            frame.red = 0xFF;
            frame.green = 0xFF;
            frame.blue = 0xFF;

            for (unsigned int i = 0; i < 10; i++) {
                frame.characters[i] = distance_message[i];
            }
            int_to_str(distance_mm, frame.characters + 10, 10);

            comm.send(frame);

            changed = false;
        }
    }


} // namespace r2d2::robos