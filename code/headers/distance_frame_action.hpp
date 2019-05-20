#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class distance_frame_action_c : public frame_action_c {
    private:
        uint16_t distance_mm;

        // Display frame types
        frame_cursor_color_s cursor_color;
        frame_cursor_position_s cursor_position;
        frame_display_8x8_character_via_cursor_s display_characters;

        static constexpr char distance_message[11] = "Distance: ";

    public:
        distance_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame);

        virtual void reply_to_data();
    }; // class distance_frame_action_c
} // namespace r2d2::robos