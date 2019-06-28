#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c flame_sensor_request;
		int flame_angle;
        bool fire_detected;
        bool big_fire;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              flame_sensor_request(comm, frame_type::FLAME_DETECTION) {
            comm.listen_for_frames({frame_type::FLAME_DETECTION});
        }
		/**
		 * Module to process data from the flame sensor
		 */
        void process_flame_sensor(frame_s frame) {
        	auto data =  frame.as_frame_type<frame_type::FLAME_DETECTION>();

        	flame_angle = data.flame_angle;
        	fire_detected = data.flame_detected;
        	big_fire = data.big_fire;

			hwlib::cout << "fire detected: " << fire_detected << "   big fire: " << big_fire << "   flame angle: " << flame_angle << hwlib::endl;

        	flame_sensor_request.mark_received();
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            flame_sensor_request.process();

            while (comm.has_data()) {
                auto frame = comm.get_data();

                // This module doesn't handel requests
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