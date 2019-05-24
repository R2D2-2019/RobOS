#pragma once

#include <display_ostream.hpp>
#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class battery_frame_action_c
        : public frame_action_c<frame_type::BATTERY_LEVEL> {
    private:
        static constexpr char battery_message[10] = "Battery: ";

        display_ostream_c ostream;

        void red_cursor();
        void green_cursor();

    public:
        battery_frame_action_c(base_comm_c &comm, frame_s &frame);

        virtual void reply_to_data() override;
    }; // class battery_frame_action_c
} // namespace r2d2::robos
