#include <distance_frame_action.hpp>

namespace r2d2::robos {
    distance_frame_action_c::distance_frame_action_c(base_comm_c &comm,
                                                     frame_s &frame,
                                                     display_ostream_c &os)
        : frame_action_c(comm, frame), ostream(os) {
    }

    void distance_frame_action_c::reply_to_data() {
        if (!changed) {
            return;
        }
        ostream << distance_message << last_frame.mm << hwlib::flush;

        changed = false;
    }
} // namespace r2d2::robos