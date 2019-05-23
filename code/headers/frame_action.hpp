#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>

#include <cstring>

namespace r2d2::robos {
    template <frame_type Type>
    class frame_action_c {
    protected:
        // set to true if the data from the frame is changed since the last call
        // of reply_to_data
        base_comm_c &comm;

        inline static frame_data_t<Type> last_frame = {};
        inline static bool changed = false;

    public:
        static constexpr frame_type action_type = Type;
        /**
         * intitialize the frame action.
         * This constructor also saves the frame when it is different from the
         * last frame
         */
        frame_action_c(base_comm_c &comm, frame_s &frame) : comm(comm) {
            auto frame_data = frame.as_frame_type<Type>();

            if (memcmp(&last_frame, &frame_data, sizeof(frame_data_t<Type>)) !=
                0) {
                last_frame = frame_data;
                changed = true;
            }
        }
        /**
         * reply to the received frame
         * this makes it possible to only send a reply when the received frame
         * is different from the last one
         */
        virtual void reply_to_data() = 0;
    }; // class frame_action_c
} // namespace r2d2::robos