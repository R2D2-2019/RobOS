#include <temperature_frame_action.hpp>

namespace r2d2::robos {
    temperature_frame_action_c::temperature_frame_action_c(base_comm_c &comm,
                                                           actions_t &actions)
        : frame_action_c(comm, frame_type::TEMPERATURE, actions) {
    }

    void temperature_frame_action_c::process_packet(frame_s &frame) {
        auto temperature_frame = frame.as_frame_type<frame_type::TEMPERATURE>();
        // If the ambient temperature of the object temperature is changed,
        // mark changed to true and set local values to the received values
        if (ambient_temperature != temperature_frame.ambient_temperature) {
            changed = true;
            ambient_temperature = temperature_frame.ambient_temperature;
        } else if (object_temperature != temperature_frame.object_temperature) {
            changed = true;
            object_temperature = temperature_frame.object_temperature;
        }
        // Data recieved, reset timer
        mark_received();
    }

    void temperature_frame_action_c::reply_to_data() {
        if (changed) {
            hwlib::cout << "Ambient temp: " << ambient_temperature / 10
                        << " Object temp: " << object_temperature / 10 << '\n';
            changed = false;
        }
    }
} // namespace r2d2::robos