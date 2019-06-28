#pragma once

#include <base_module.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class module_c : public base_module_c {
    private:
        timed_request_c manual_control_request_speed;
        timed_request_c manual_control_request_steer;
        timed_request_c manual_control_request_direction;
        int8_t speed = 0;
        int8_t steering_angle = 0;
        bool brake = false;
        bool flag_for_send = 0;
        bool forward = true;

    public:
        /**
         * Module can listen up to 8 frame_types
         */
        module_c(base_comm_c &comm)
            : base_module_c(comm),
              manual_control_request_speed(comm,
                                           frame_type::MANUAL_CONTROL_SLIDER),
              manual_control_request_steer(comm,
                                           frame_type::MANUAL_CONTROL_JOYSTICK),
              manual_control_request_direction(
                  comm, frame_type::MANUAL_CONTROL_BUTTON) {
            comm.listen_for_frames({frame_type::MANUAL_CONTROL_SLIDER,
                                    frame_type::MANUAL_CONTROL_JOYSTICK,
                                    frame_type::MANUAL_CONTROL_BUTTON});
        }

        void process_movement_control_speed(const frame_s &frame);

        void process_movement_control_steer(const frame_s &frame);

        void process_movement_control_direction(const frame_s &frame);

        /**
         * Let the module process data
         */
        void process() override;
    };
} // namespace r2d2::robos