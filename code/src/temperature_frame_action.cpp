#include <temperature_frame_action.hpp>

namespace r2d2::robos {
    temperature_frame_action_c::temperature_frame_action_c(base_comm_c &comm,
                                                           frame_s &frame)
        : frame_action_c(comm, frame),
          ostream(comm, claimed_display_cursor::ROBOS_TEMPERATURE_CURSOR,
                  {0, 0, 0}, 0, 30) {
    }

    void temperature_frame_action_c::reply_to_data() {
        if (!changed) {
            return;
        }
        // hwlib::cout << "Ambient temp: " << ambient_temperature / 10
        //            << " Object temp: " << object_temperature / 10 <<
        //            '\n';
        ostream << temperature_message << (last_frame.object_temperature / 10)
                << hwlib::flush;

        changed = false;
    }
} // namespace r2d2::robos