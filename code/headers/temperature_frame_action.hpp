#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class temperature_frame_action_c
        : public frame_action_c<frame_type::TEMPERATURE> {
    private:
        // Display frame types
        frame_cursor_color_s cursor_color;
        frame_cursor_position_s cursor_position;
        frame_display_8x8_character_via_cursor_s display_characters;

        static constexpr char temperature_message[11] = "Obj temp: ";

    public:
        temperature_frame_action_c(base_comm_c &comm, frame_s &frame);

        virtual void reply_to_data() override;
    }; // class temperature_frame_action_c
} // namespace r2d2::robos