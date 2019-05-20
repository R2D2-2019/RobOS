#pragma once

#include <hwlib.hpp>
#include <frame_action.hpp>

namespace r2d2::robos {
    class battery_frame_action_c : public frame_action_c {
    private:
        uint8_t battery_percentage;

        static constexpr char battery_message[10] = "Battery: ";

    public:
        battery_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame) override;

        virtual void reply_to_data();
    }; // class battery_frame_action_c
} // namespace r2d2::robos

