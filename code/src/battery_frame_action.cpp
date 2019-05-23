#include <battery_frame_action.hpp>

#include <int_to_string.hpp>

namespace r2d2::robos {
    battery_frame_action_c::battery_frame_action_c(base_comm_c &comm,
                                                   frame_s &frame)
        : frame_action_c(comm, frame) {
        static constexpr uint8_t cursor_id =
            static_cast<uint8_t>(claimed_display_cursor::ROBOS_POWER_CURSOR);
        cursor_color.cursor_id = cursor_id;
        cursor_position.cursor_id = cursor_id;
        display_characters.cursor_id = cursor_id;

        // Set battery information to the top left corner
        cursor_position.cursor_x = 0;
        cursor_position.cursor_y = 0;
        // Send cursor position to display, this only has to be done once
        // since the position won't change
        comm.send(cursor_position);
    }

    void battery_frame_action_c::red_cursor(frame_cursor_color_s &frame) {
        frame.red = 255;
        frame.green = 0;
        frame.blue = 0;
    }
    void battery_frame_action_c::green_cursor(frame_cursor_color_s &frame) {
        frame.red = 0;
        frame.green = 255;
        frame.blue = 0;
    }

    void battery_frame_action_c::reply_to_data() {
        if (changed) {

            // If battery percentage is under the 30 percent, make the text red
            // Else make the text green
            if (last_frame.percentage < 30) {
                red_cursor(cursor_color);
            } else {
                green_cursor(cursor_color);
            }
            comm.send(cursor_color);

            for (unsigned int i = 0; i < 10; i++) {
                display_characters.characters[i] = battery_message[i];
            }
            display_characters.characters[10] = '\0';
            cursor_position.cursor_x = 0;
            comm.send(cursor_position);
            comm.send(display_characters);

            cursor_position.cursor_x = 100;
            for (unsigned int i = 0; i < 10; i++) {
                display_characters.characters[i] = ' ';
            }
            display_characters.characters[10] = '\0';
            int_to_str(last_frame.percentage, display_characters.characters);
            comm.send(cursor_position);
            comm.send(display_characters);

            changed = false;
        }
    }
} // namespace r2d2::robos