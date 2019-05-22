#pragma once

#include <base_module.hpp>
#include <hwlib.hpp>

namespace r2d2::test_module {
    class module_c : public base_module_c {
        hwlib::target::pin_adc adc{hwlib::target::ad_pins::a10};

    protected:
    public:
        /**
         * @param comm the communication bus
         */
        module_c(base_comm_c &comm) : base_module_c(comm) {

            // Set up listeners
            comm.listen_for_frames({r2d2::frame_type::BATTERY_LEVEL});
        }

        uint8_t current_value = 30;

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

                frame_battery_level_s battery_level;
                battery_level.voltage = adc.read() / 6;
                battery_level.percentage = battery_level.voltage * 2;

                comm.send(battery_level);
            }
        }
    };
} // namespace r2d2::test_module