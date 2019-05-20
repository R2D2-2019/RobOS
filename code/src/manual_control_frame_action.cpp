#include <../headers/manual_control_frame_action.hpp>

namespace r2d2::robos {
    bool operator!=(frame_manual_control_s &lhs, frame_manual_control_s &rhs) {
        return (lhs.brake != rhs.brake) || (lhs.speed != rhs.speed) ||
               (lhs.rotation != rhs.rotation);
    }

    manual_control_frame_action_c::manual_control_frame_action_c(
        base_comm_c &comm, actions_t &actions)
        : frame_action_c(comm, frame_type::MANUAL_CONTROL, actions) {
    }

    void manual_control_frame_action_c::process_packet(frame_s &frame) {
        auto man_control_frame =
            frame.as_frame_type<frame_type::MANUAL_CONTROL>();

        if (man_control != man_control_frame) {
            man_control = man_control_frame;
            changed = true;
        }
        // Data recieved, reset timer
        mark_received();
    }

    void manual_control_frame_action_c::reply_to_data() {
        if (changed) {
            frame_movement_control_s frame;

            frame.brake = man_control.brake;
            frame.rotation = man_control.rotation;
            frame.speed = man_control.speed;

            comm.send(frame);

            // hwlib::cout << man_control.brake << ", " <<
            // man_control.rotation
            //             << ", " << man_control.speed << hwlib::endl;

            changed = false;
        }
    }
} // namespace r2d2::robos