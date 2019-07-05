#pragma once

#include <robos_role.hpp>

namespace r2d2::robos {

    class moving_platform_role_c : public robos_role_c {
    public:
        /**
         * @brief
         * Constructor moving_platform_role_c
         *
         * The default constructor is empty.
         */
        moving_platform_role_c();

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