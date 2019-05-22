#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class frame_action_c : public timed_request_c {
    public:
        // this array is suppliedf to constructors, to prevent copy-pasting the
        // whole type definition, this type is created
        using actions_t = std::array<frame_action_c *, frame_type::COUNT>;

    protected:
        // set to true if the data from the frame is changed since the last call
        // of reply_to_data
        bool changed = false;

    public:
        /**
         * intitialize the frame action.
         * This constructor also saves it's pointer in the supplied array
         */
        frame_action_c(base_comm_c &comm, frame_type type, actions_t &actions)
            : timed_request_c(comm, type) {
            actions[type] = this;
        }
        /**
         * intitialize the frame action.
         * This constructor also saves it's pointer in the supplied array
         */
        frame_action_c(base_comm_c &comm, frame_type type, actions_t &actions,
                       uint32_t timeout)
            : timed_request_c(comm, type, timeout) {
            actions[type] = this;
        }

        /**
         * process the packet
         */
        virtual void process_packet(frame_s &frame) = 0;
        /**
         * reply to the received frames
         * this makes it possible to only send a reply when the received frame
         * is different from the last one
         */
        virtual void reply_to_data() = 0;
    }; // class frame_action_c
} // namespace r2d2::robos