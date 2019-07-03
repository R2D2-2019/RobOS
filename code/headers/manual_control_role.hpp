#pragma once

#include <robos_role.hpp>

namespace r2d2::robos {

    class manual_control_role_c : public robos_role_c {
    private:
        int8_t speed = 0;
        int8_t steering_angle = 0;
        bool brake = false;
        bool flag_for_send = 0;
        bool forward = true;

    public:
        /**
         * @brief
         * Constructor manual_control_role_c
         *
         * The default constructor is empty.
         */
        manual_control_role_c();

        /**
         * @brief
         * This function returns the name of the role.
         * @detail
         * This must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        robos_roles get_role_name() override;

        void process_movement_control_speed(const frame_s &frame);

        void process_movement_control_steer(const frame_s &frame);

        void process_movement_control_direction(const frame_s &frame);

        /**
         * @brief
         * This function handles the tasks of the role.
         *
         * @param std::array<frame_type, 10>: frames
         * The required frames to process this role.
         * @detail
         * This function will receive data of certain modules and
         * send the data to other modules if requirements are met.
         * This function must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        uint8_t run(ringbuffer_c<frame_s, 32> &ringbuffer) override;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         */
        uint8_t cleanup() override;
    };
} // namespace r2d2::robos