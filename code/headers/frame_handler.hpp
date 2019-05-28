#pragma once

#include <array>
#include <display_ostream.hpp>

#include <battery_frame_action.hpp>
#include <distance_frame_action.hpp>
#include <manual_control_frame_action.hpp>
#include <temperature_frame_action.hpp>

namespace r2d2::robos {
    class frame_handler_c {
    private:
        base_comm_c &comm;

        display_ostream_c power_ostream{
            comm, claimed_display_cursor::ROBOS_POWER_CURSOR, 0, 0};
        display_ostream_c distance_ostream{
            comm, claimed_display_cursor::ROBOS_DISTANCE_CURSOR, 0, 16};
        display_ostream_c temperature_ostream{
            comm, claimed_display_cursor::ROBOS_TEMPERATURE_CURSOR, 0, 32};

    public:
        frame_handler_c(base_comm_c &comm) : comm(comm) {
        }

        void process(frame_s &frame) {
            switch (frame.type) {
            case battery_frame_action_c::action_type:
                battery_frame_action_c(comm, frame, power_ostream)
                    .reply_to_data();
                break;
            case distance_frame_action_c::action_type:
                distance_frame_action_c(comm, frame, distance_ostream)
                    .reply_to_data();
                break;
            case manual_control_frame_action_c::action_type:
                manual_control_frame_action_c(comm, frame).reply_to_data();
                break;
            case temperature_frame_action_c::action_type:
                temperature_frame_action_c(comm, frame, temperature_ostream)
                    .reply_to_data();
                break;
            // More frame types...
            default:
                // No idea what this frame is, do nothing
                break;
            }
        }
    }; // namespace r2d2::robos
} // namespace r2d2::robos