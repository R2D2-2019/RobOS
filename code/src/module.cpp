#include "module.hpp"

namespace r2d2::robos {

    void module_c::process_movement_control_speed(const frame_s &frame) {
        auto data = frame.as_frame_type<frame_type::MANUAL_CONTROL_SLIDER>();

        // convert to moving platform
        // slider id 0 is left peddel and slider id 1 is right peddel

        hwlib::cout << "Slider_id: " << data.slider_id << "\n";
        hwlib::cout << "Value: " << data.value << "\n";
        if (data.slider_id == 0) {
            brake = true;
            speed = 0;
        } else {
            brake = false;
            speed = data.value;
        }
        flag_for_send = 1;
        // Data recieved, reset timer
        manual_control_request_speed.mark_received();
    }

    void module_c::process_movement_control_steer(const frame_s &frame) {
        auto data = frame.as_frame_type<frame_type::MANUAL_CONTROL_JOYSTICK>();

        // convert to moving platform
        steering_angle = data.value_x;
        flag_for_send = 1;
        // Data recieved, reset timer
        manual_control_request_steer.mark_received();
    }
    /**
     * Let the module process data
     */
    void module_c::process() {
        // Set out all polling requests
        // manual_control_request_speed.process();
        // manual_control_request_steer.process();
        comm.request(frame_type::MANUAL_CONTROL_SLIDER);
        comm.request(frame_type::MANUAL_CONTROL_JOYSTICK);

        while (comm.has_data()) {
            auto frame = comm.get_data();

            // This module doesn't handel requests
            if (frame.request) {
                continue;
            }

            // Process the frame
            switch (frame.type) {
            case frame_type::MANUAL_CONTROL_SLIDER:
                // hwlib::cout << "manual slider\n";
                process_movement_control_speed(frame);
                break;
            case frame_type::MANUAL_CONTROL_JOYSTICK:
                // hwlib::cout << "manual steer\n";
                process_movement_control_steer(frame);
                break;
            default:
                break;
            }

            if (flag_for_send) {
                flag_for_send = 0;

                // send frame to moving platform
                frame_movement_control_s movement;

                movement.brake = brake;
                movement.rotation = steering_angle;
                movement.speed = speed;

                comm.send(movement);
            }
        }
    }
} // namespace r2d2::robos