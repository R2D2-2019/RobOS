#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>
#include <timed_request.hpp>

// needed for int_to_str
#include <charconv>

namespace r2d2::robos {
    class frame_action_c : public timed_request_c {
    public:
        using actions_t = std::array<frame_action_c *, frame_type::COUNT>;

    protected:
        bool changed = false;

        void int_to_str(unsigned int i, char *str, unsigned int lenght) {
            std::to_chars(str, str + lenght, i);
        }

    public:
        frame_action_c(base_comm_c &comm, frame_type type, actions_t &actions)
            : timed_request_c(comm, type) {
            actions[type] = this;
        }
        frame_action_c(base_comm_c &comm, frame_type type, actions_t &actions,
                       uint32_t timeout)
            : timed_request_c(comm, type, timeout) {
            actions[type] = this;
        }

        /**
         * process the packet
         */
        virtual void process_packet(frame_s &frame) = 0;

        virtual void reply_to_data() = 0;
    }; // class frame_action_c
} // namespace r2d2::robos