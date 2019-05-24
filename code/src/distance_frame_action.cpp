#include <distance_frame_action.hpp>

#include <int_to_string.hpp>

namespace r2d2::robos {
    distance_frame_action_c::distance_frame_action_c(base_comm_c &comm,
                                                     frame_s &frame)
        : frame_action_c(comm, frame) {
        static constexpr uint8_t cursor_id =
            static_cast<uint8_t>(claimed_display_cursor::ROBOS_DISTANCE_CURSOR);
        cursor_color.cursor_id = cursor_id;
        cursor_position.cursor_id = cursor_id;
        display_characters.cursor_id = cursor_id;

        // Set cursor to Black as default
        cursor_color.red = 0x00;
        cursor_color.green = 0x00;
        cursor_color.blue = 0x00;
        comm.send(cursor_color);

        // Set battery information to the top left corner
        cursor_position.cursor_x = 0;
        cursor_position.cursor_y = 2 * 10;
        comm.send(cursor_position);

        for (unsigned int i = 0; i < 11; i++) {
            display_characters.characters[i] = distance_message[i];
        }
        display_characters.characters[11] = '\0';
        comm.send(display_characters);

        cursor_position.cursor_x = 100;
    }

    void distance_frame_action_c::reply_to_data() {
        if (!changed) {
            return;
        }
        for (unsigned int i = 0; i < 11; i++) {
            display_characters.characters[i] = ' ';
        }
        display_characters.characters[11] = '\0';
        int_to_str(last_frame.mm, display_characters.characters);
        comm.send(cursor_position);
        comm.send(display_characters);

        changed = false;
    }
} // namespace r2d2::robos