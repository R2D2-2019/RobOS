#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c battery_request;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm) 
            : base_module_c(comm),
              battery_request(comm, frame_type::BATTERY_LEVEL) {
            comm.listen_for_frames({
                frame_type::BATTERY_LEVEL
            });
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            battery_request.process();

            while (comm.has_data()) {
                auto frame = comm.get_data();

                // This module doesn't handel requests
                if(frame.request) {
                    continue;
                }

                // Process the frame
                switch (frame.type) {
                    case frame_type::BATTERY_LEVEL:
                        {
                            // Create object to read battery struct data
                            auto battery_percentage = frame.as_frame_type<frame_type::BATTERY_LEVEL>().percentage;
                            
                            hwlib::cout << "battery percentage: " << static_cast<int>(battery_percentage) << "%" << hwlib::endl;
                            if(battery_percentage <= 10) {
                                frame_activity_led_state_s led_state;
                                led_state.state = true;
                            } else {
                                frame_activity_led_state_s led_state;
                                led_state.state = false;
                            }
                            // Data recieved, reset timer
                            battery_request.mark_received();
                        }
                        break;
                    default: break;
                }
            }
        }
    };
}