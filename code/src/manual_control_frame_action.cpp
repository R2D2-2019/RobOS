#include <manual_control_frame_action.hpp>

namespace r2d2::robos {
    template <>
    frame_data_t<manual_control_frame_action_c::action_type> frame_action_c<
        manual_control_frame_action_c::action_type>::last_frame = {};
    template <>
    bool frame_action_c<manual_control_frame_action_c::action_type>::changed =
        false;

    manual_control_frame_action_c::manual_control_frame_action_c(
        base_comm_c &comm, frame_s &frame)
        : frame_action_c(comm, frame) {
    }

    void manual_control_frame_action_c::reply_to_data() {
        if (changed) {
            frame_movement_control_s frame;

            frame.brake = last_frame.brake;
            frame.rotation = last_frame.rotation;
            frame.speed = last_frame.speed;

            comm.send(frame);

            changed = false;
        }
    }
} // namespace r2d2::robos