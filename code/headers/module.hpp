#pragma once

#include <frame_handler.hpp>

#include <base_module.hpp>
#include <timed_request.hpp>

#include <array>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        std::array<timed_request_c, frame_type::COUNT> requests = {};
        frame_handler_c handler;

    public:
        /**
         * @param comm the communication bus
         */
        module_c(base_comm_c &comm) : base_module_c(comm), handler(comm) {
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
                handler.process(frame);

                // Data recieved, reset timer
                auto &request = requests[frame.type];
                if (request.get_type() != frame_type::NONE) {
                    request.mark_received();
                }
            }
        }
    }; // class module_c
} // namespace r2d2::robos