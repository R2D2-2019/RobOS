#pragma once

#include <battery_frame_action.hpp>
#include <distance_frame_action.hpp>
#include <manual_control_frame_action.hpp>
#include <temperature_frame_action.hpp>

namespace r2d2::robos {
    class frame_handler_c {
    public:
        static void process(base_comm_c &comm, frame_s &frame) {
            switch (frame.type) {
            case battery_frame_action_c::action_type:
                battery_frame_action_c(comm, frame).reply_to_data();
                break;
            case distance_frame_action_c::action_type:
                distance_frame_action_c(comm, frame).reply_to_data();
                break;
            case manual_control_frame_action_c::action_type:
                manual_control_frame_action_c(comm, frame).reply_to_data();
                break;
            case temperature_frame_action_c::action_type:
                temperature_frame_action_c(comm, frame).reply_to_data();
                break;
            // More frame types...
            default:
                // No idea what this frame is, do nothing
                break;
            }
        }
    };
} // namespace r2d2::robos