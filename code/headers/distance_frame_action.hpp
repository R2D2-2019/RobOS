#pragma once

#include <hwlib.hpp>
#include <frame_action.hpp>

namespace r2d2::robos {
    class distance_frame_action_c : public frame_action_c {
    private:
        uint16_t distance_mm;

        static constexpr char distance_message[11] = "Distance: ";

    public:
        distance_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame);

        virtual void reply_to_data();
    }; // class distance_frame_action_c
} // namespace r2d2::robos