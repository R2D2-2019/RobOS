#pragma once

#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class manual_control_frame_action_c : public frame_action_c {
    private:
        frame_manual_control_s man_control;

    public:
        manual_control_frame_action_c(base_comm_c &comm, actions_t &actions);

        void process_packet(frame_s &frame) override;

        virtual void reply_to_data();
    }; // class manual_control_frame_action_c
} // namespace r2d2::robos