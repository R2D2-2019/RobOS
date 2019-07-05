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
         *
         * @return enum role of enum class robos_roles
         */
        robos_roles get_role_name() override;

        /**
         * @brief
         * Converts the manual control sliders to moving platform frames.
         *
         * @detail
         * The sliders are converted to the speed frame of moving platform.
         * This will change the speed of manual control.
         *
         * @param const frame_manual_control_slider_s &frame
         */
        void process_movement_control_speed(
            const frame_manual_control_slider_s &frame);

        /**
         * @brief
         * Converts the manual control joystick to moving platform frames
         *
         * @detail
         * The joystick is converted to the steering_angle frame of moving
         * platform. This will rotate the moving platform in a certain angle.
         *
         * @param const frame_manual_control_joystick_s &frame
         */
        void process_movement_control_steer(
            const frame_manual_control_joystick_s &frame);

        /**
         * @brief
         * Converts the manual control direction to moving platform frames
         *
         * @detail
         * The direction is converted to the forward frame of moving platform.
         * This will move the platform forward or not.
         *
         * @param const frame_manual_control_joystick_s &frame
         */
        void process_movement_control_direction(
            const frame_manual_control_button_s &frame);

        /**
         * @brief
         * This function handles the tasks of the role.
         *
         * @detail
         * This function will receive data of certain modules and
         * send the data to other modules via can bus.
         * This function must be overridden by the child class
         * of the abstract class robos_role_c.
         *
         * @param ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer
         * The required frames to process this role.
         *
         * @param base_comm_c & comm
         * Reference to base_comm_c.
         * Required to send packets on can bus.
         *
         * @return uint8_t
         */
        uint8_t run(ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer,
                    base_comm_c &comm) override;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         *
         * @return uint8_t
         */
        uint8_t cleanup() override;
    };
} // namespace r2d2::robos