#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class temperature_frame_action_c : public frame_action_c {
    private:
        int16_t ambient_temperature;
        int16_t object_temperature;

        static constexpr char distance_message[14] = "Temperature: ";

    public:
        temperature_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame);

        virtual void reply_to_data();
    }; // class temperature_frame_action_c
} // namespace r2d2::robos