#pragma once

#include <display_ostream.hpp>
#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class distance_frame_action_c
        : public frame_action_c<frame_type::DISTANCE> {
    private:
        display_ostream_c ostream;

        static constexpr char distance_message[11] = "Distance: ";

    public:
        distance_frame_action_c(base_comm_c &comm, frame_s &frame);

        virtual void reply_to_data() override;
    }; // class distance_frame_action_c
} // namespace r2d2::robos