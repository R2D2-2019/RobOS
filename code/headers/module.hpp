#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c manual_control_request_speed;
        timed_request_c manual_control_request_steer;
        int8_t speed = 0;
        int8_t steering_angle = 0;
        bool brake = false;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              manual_control_request_speed(comm,
                                           frame_type::MANUAL_CONTROL_SLIDER),
              manual_control_request_steer(
                  comm, frame_type::MANUAL_CONTROL_JOYSTICK) {
            comm.listen_for_frames({frame_type::MANUAL_CONTROL_SLIDER,
                                    frame_type::MANUAL_CONTROL_JOYSTICK});
        }

        void process_movement_control_speed(frame_s frame) {
            auto data =
                frame.as_frame_type<frame_type::MANUAL_CONTROL_SLIDER>();

            // convert to moving platform
            // slider id 0 is left peddel and slider id 1 is right peddel

            if (data.slider_id == 0) {
                brake = true;
                speed = 0;
            } else {
                brake = false;
                speed = data.value;
            }
            // send frame to moving platform
            frame_movement_control_s movement;

            movement.brake = brake;
            movement.rotation = steering_angle;
            movement.speed = speed;

            comm.send(movement);

            // Data recieved, reset timer
            manual_control_request_speed.mark_received();
        }

        void process_movement_control_steer(frame_s frame) {
            auto data =
                frame.as_frame_type<frame_type::MANUAL_CONTROL_JOYSTICK>();

            // convert to moving platform
            steering_angle = data.value_x;

            // send frame to moving platform
            frame_movement_control_s movement;

            movement.brake = brake;
            movement.rotation = steering_angle;
            movement.speed = speed;

            comm.send(movement);

            // Data recieved, reset timer
            manual_control_request_steer.mark_received();
        }
        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
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
                    process_movement_control_speed(frame);
                    break;
                case frame_type::MANUAL_CONTROL_JOYSTICK:
                    process_movement_control_steer(frame);
                    break;
                default:
                    break;
                }
            }
        }
    };
} // namespace r2d2::robos