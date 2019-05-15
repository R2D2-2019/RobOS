#pragma once

#include <base_module.hpp>

namespace r2d2::test_module {
    class module_c : public base_module_c {
    protected:
        /**
         * The button pin.
         */
        hwlib::pin_in &battery_pin;

    public:
        /**
         * @param comm
         * @param button
         */
        module_c(base_comm_c &comm, hwlib::pin_in &battery_pin)
            : base_module_c(comm), button(battery_pin) {

            // Set up listeners
            comm.listen_for_frames(
                {
                    r2d2::frame_type::BATTERY_LEVEL
                }
            );
        }

        uint8_t current_value = 100;

        /**
         * Let the module process data.
         */
        void process() override {
            while (comm.has_data()) {
                auto frame = comm.get_data();

                // Only handle requests
                if (!frame.request) {
                    continue;
                }

                // Get button state, create frame and send
                frame_battery_level_s battery_level;
                if(current_value > 0) {
                    current_value -= 1;
                    battery_level.percentage = current_value;
                }else {
                    current_value = 100;
                }

                comm.send(battery_level);
            }
        }
    };
}