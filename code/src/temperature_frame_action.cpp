#include <temperature_frame_action.hpp>

namespace r2d2::robos {
    temperature_frame_action_c::temperature_frame_action_c(
        base_comm_c &comm, frame_s &frame, display_ostream_c &os)
        : frame_action_c(comm, frame), ostream(os) {
    }

    void temperature_frame_action_c::reply_to_data() {
        if (!changed) {
            return;
        }
        ostream << temperature_message << (last_frame.object_temperature / 10)
                << hwlib::flush;

        changed = false;
    }
} // namespace r2d2::robos