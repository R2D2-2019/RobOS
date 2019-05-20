#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class battery_frame_action_c : public frame_action_c {
    private:
        uint8_t battery_percentage;

        static constexpr char battery_message[10] = "Battery: ";

        // Display frame types
        frame_cursor_color_s cursor_color;
        frame_cursor_position_s cursor_position;
        frame_display_8x8_character_via_cursor_s display_characters;

        void red_cursor(frame_cursor_color_s &frame);
        void green_cursor(frame_cursor_color_s &frame);

    public:
        battery_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame) override;

        virtual void reply_to_data();
    }; // class battery_frame_action_c
} // namespace r2d2::robos
