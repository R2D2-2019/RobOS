#pragma once

#include <battery_frame_action.hpp>
#include <distance_frame_action.hpp>
#include <manual_control_frame_action.hpp>
#include <temperature_frame_action.hpp>

#include <base_module.hpp>
#include <timed_request.hpp>

#include <array>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        frame_action_c::actions_t actions = {};

        battery_frame_action_c battery_action;
        manual_control_frame_action_c manual_control_action;
        distance_frame_action_c distance_action;
        temperature_frame_action_c temperature_action;

        std::array<timed_request_c, frame_type::COUNT> requests = {};

    public:
        /**
         * @param comm the communication bus
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              // initialize all frame actions
              battery_action(comm, actions),
              manual_control_action(comm, actions),
              distance_action(comm, actions),
              temperature_action(comm, actions) {
            // Note: module can listen up to 8 frame_types as of now
            comm.listen_for_frames(
                {frame_type::BATTERY_LEVEL, frame_type::MANUAL_CONTROL,
                 frame_type::DISTANCE, frame_type::TEMPERATURE});

            for (const uint8_t type : comm.get_accepted_frame_types()) {
                requests[type] = {&comm, static_cast<frame_type>(type)};
            }
        }

        /**
         * Let the module process data
         */
        void process() override {
            // Set out all polling requests
            for (auto &request : requests) {
                if (request.get_type() != frame_type::NONE) {
                    request.request_packet();
                }
            }

            // process received frames
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

                // Data recieved, reset timer
                auto &request = requests[frame.type];
                if (request.get_type() != frame_type::NONE) {
                    request.mark_received();
                }
            }

            // reply to received frames, this makes it possible to only send a
            // reply when the received frame is different from the last one
            for (auto action : actions) {
                if (action != nullptr) {
                    action->reply_to_data();
                }
            }
        }
    }; // class module_c
} // namespace r2d2::robos