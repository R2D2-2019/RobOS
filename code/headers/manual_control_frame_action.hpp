#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class manual_control_frame_action_c
        : public frame_action_c<frame_type::MANUAL_CONTROL> {
    public:
        manual_control_frame_action_c(base_comm_c &comm, frame_s &frame);

        virtual void reply_to_data() override;
    }; // class manual_control_frame_action_c
} // namespace r2d2::robos