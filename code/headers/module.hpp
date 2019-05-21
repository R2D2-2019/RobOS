#pragma once

#include <base_module.hpp>
#include <frame_action.hpp>

#include <battery_frame_action.hpp>
#include <distance_frame_action.hpp>
#include <manual_control_frame_action.hpp>
#include <temperature_frame_action.hpp>

#include <array>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        frame_action_c::actions_t actions = {0};

        battery_frame_action_c battery_action;
        manual_control_frame_action_c manual_control_action;
        distance_frame_action_c distance_action;
        temperature_frame_action_c temperature_action;

    public:
        /**
         * @param comm the communication bus
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              battery_action(comm, actions),
              manual_control_action(comm, actions),
              distance_action(comm, actions),
              temperature_action(comm, actions) {
            // Module can listen up to 8 frame_types as of now
            comm.listen_for_frames(
                {frame_type::BATTERY_LEVEL, frame_type::MANUAL_CONTROL,
                 frame_type::DISTANCE, frame_type::TEMPERATURE});
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            for (auto action : actions) {
                if (action != nullptr) {
                    action->request_packet();
                }
            }

            while (comm.has_data()) {
                auto frame = comm.get_data();
                // This module doesn't handel requests
                if (frame.request) {
                    continue;
                }

                // process the received packet using the appropriate
                // frame-handler
                frame_action_c *action = actions[frame.type];
                if (action != nullptr) {
                    action->process_packet(frame);
                }
            }

            for (auto action : actions) {
                if (action != nullptr) {
                    action->reply_to_data();
                }
            }
        }
    }; // class module_c
} // namespace r2d2::robos