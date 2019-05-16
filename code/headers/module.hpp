#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c battery_request;
        timed_request_c manual_control_request;
        timed_request_c distance_sensor_request;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              battery_request(comm, frame_type::BATTERY_LEVEL),
              manual_control_request(comm, frame_type::MOVEMENT_CONTROL),
              distance_sensor_request(comm, frame_type::DISTANCE) {
            comm.listen_for_frames({frame_type::BATTERY_LEVEL,
                                    frame_type::MOVEMENT_CONTROL,
                                    frame_type::DISTANCE});
        }

        void process_battery_level(frame_s frame) {
            // Create object to read battery struct data
            auto battery_percentage =
                frame.as_frame_type<frame_type::BATTERY_LEVEL>().percentage;

            hwlib::cout << "battery percentage: "
                        << static_cast<int>(battery_percentage) << "%"
                        << hwlib::endl;
            // Data recieved, reset timer
            battery_request.mark_received();
        }

        void process_distance(frame_s frame) {
            auto distance_frame = frame.as_frame_type<frame_type::DISTANCE>();

            // Data recieved, reset timer
            distance_sensor_request.mark_received();
        }
        void process_movement_control(frame_s frame) {
            auto distance_frame =
                frame.as_frame_type<frame_type::MOVEMENT_CONTROL>();

            // Data recieved, reset timer
            manual_control_request.mark_received();
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            battery_request.process();
            manual_control_request.process();
            distance_sensor_request.process();

            while (comm.has_data()) {
                auto frame = comm.get_data();

                // This module doesn't handel requests
                if (frame.request) {
                    continue;
                }

                // Process the frame
                switch (frame.type) {
                case frame_type::BATTERY_LEVEL:
                    process_battery_level(frame);
                    break;
                case frame_type::DISTANCE:
                    process_distance(frame);
                    break;
                case frame_type::MOVEMENT_CONTROL:
                    process_movement_control(frame);
                    break;
                default:
                    break;
                }
            }
        }
    };
} // namespace r2d2::robos