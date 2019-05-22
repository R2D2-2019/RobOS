#include <temperature_frame_action.hpp>

#include <int_to_string.hpp>

namespace r2d2::robos {
    temperature_frame_action_c::temperature_frame_action_c(base_comm_c &comm,
                                                           actions_t &actions)
        : frame_action_c(comm, frame_type::TEMPERATURE, actions) {
        static constexpr uint8_t cursor_id = static_cast<uint8_t>(
            claimed_display_cursor::ROBOS_TEMPERATURE_CURSOR);
        cursor_color.cursor_id = cursor_id;
        cursor_position.cursor_id = cursor_id;
        display_characters.cursor_id = cursor_id;

        // Set cursor colour to green and send the frame
        cursor_color.red = 0;
        cursor_color.green = 255;
        cursor_color.blue = 0;
        comm.send(cursor_color);
    }

    void temperature_frame_action_c::process_packet(frame_s &frame) {
        auto temperature_frame = frame.as_frame_type<frame_type::TEMPERATURE>();
        // If the ambient temperature of the object temperature is changed,
        // mark changed to true and set local values to the received values
        if (ambient_temperature != temperature_frame.ambient_temperature) {
            changed = true;
            ambient_temperature = temperature_frame.ambient_temperature;
        } else if (object_temperature != temperature_frame.object_temperature) {
            changed = true;
            object_temperature = temperature_frame.object_temperature;
        }
        // Data recieved, reset timer
        mark_received();
    }

    void temperature_frame_action_c::reply_to_data() {
        if (changed) {
            // hwlib::cout << "Ambient temp: " << ambient_temperature / 10
            //            << " Object temp: " << object_temperature / 10 <<
            //            '\n';
            for (unsigned int i = 0; i < 11; i++) {
                display_characters.characters[i] = temperature_message[i];
            }
            display_characters.characters[11] = '\0';
            cursor_position.cursor_x = 0;
            cursor_position.cursor_y = 3 * 10;
            comm.send(cursor_position);
            comm.send(display_characters);

            cursor_position.cursor_x = 100;
            for (unsigned int i = 0; i < 10; i++) {
                display_characters.characters[i] = ' ';
            }
            display_characters.characters[10] = '\0';
            int_to_str(object_temperature / 10, display_characters.characters);
            comm.send(cursor_position);
            comm.send(display_characters);
            changed = false;
        }
    }
} // namespace r2d2::robos