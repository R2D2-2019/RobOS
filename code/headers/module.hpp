#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c flame_sensor_request;
        int prev_flame_angle;
        bool prev_fire_detected;
        bool prev_big_fire;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              flame_sensor_request(comm, frame_type::FLAME_DETECTION, 500) {
            comm.listen_for_frames({frame_type::FLAME_DETECTION});
        }
        /**
         * Module to process data from the flame sensor
         */
        void process_flame_sensor(frame_s frame) {
            auto data = frame.as_frame_type<frame_type::FLAME_DETECTION>();

            flame_sensor_request.mark_received();

            frame_movement_control_s movement;

            // check if something new happend, if not, do nothing.
            if (data.flame_angle == prev_flame_angle &&
                data.flame_detected == prev_fire_detected &&
                data.big_fire == prev_big_fire) {
                return;
            } else {
                prev_flame_angle = data.flame_angle;
                prev_fire_detected = data.flame_detected;
                prev_big_fire = data.big_fire;
            }

            hwlib::cout << "fire detected: " << prev_fire_detected
                        << "   big fire: " << prev_big_fire
                        << "   flame angle: " << prev_flame_angle << hwlib::endl;

            if (prev_fire_detected && !prev_big_fire) {
                movement.brake = false;
                movement.rotation = prev_flame_angle;
                movement.speed = 20;
            } else {
                movement.brake = true;
                movement.rotation = 0;
                movement.speed = 0;
            }

            comm.send(movement);
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            flame_sensor_request.process();

            while (comm.has_data()) {
                auto frame = comm.get_data();

                // This module doesn't handle requests
                if (frame.request) {
                    continue;
                }

                // Process the frame
                switch (frame.type) {

                case frame_type::FLAME_DETECTION:
                    process_flame_sensor(frame);
                    break;
                default:
                    break;
                }
            }
        }
    };
} // namespace r2d2::robos