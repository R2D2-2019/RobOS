#include <distance_frame_action.hpp>

namespace r2d2::robos {
    distance_frame_action_c::distance_frame_action_c(base_comm_c &comm,
                                                     actions_t &actions)
        : frame_action_c(comm, frame_type::DISTANCE, actions) {

        // init color
        cursor_color.red = 0xFF;
        cursor_color.green = 0xFF;
        cursor_color.blue = 0xFF;
        cursor_color.cursor_id = distance_cursor_type;
        comm.send(cursor_color);

        // init position
        cursor_position.cursor_id = distance_cursor_type;
        cursor_position.cursor_x = 0;
        cursor_position.cursor_y = (8 * 2);
        comm.send(cursor_position);
        cursor_position.cursor_x = (8 * 10);

        // init characters
        cursor_chars.cursor_id = distance_cursor_type;
        for (unsigned int i = 0; i < 11; i++) {
            cursor_chars.characters[i] = distance_message[i];
        }
        comm.send(cursor_chars);
        for (unsigned int i = 0; i < 11; i++) {
            cursor_chars.characters[i] = '\0';
        }
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
            int_to_str(distance_mm, cursor_chars.characters + 10, 10);

            comm.send(cursor_position);
            comm.send(cursor_chars);

            changed = false;
        }
    }

} // namespace r2d2::robos