#pragma once

#include <robos_role.hpp>

namespace r2d2::robos {

    class robos_example_role_c : public robos_role_c {
    public:

        /**
         * @brief
         * Constructor robos_example_role_c
         *
         * The default constructor is empty.
         */
        robos_example_role_c();

        /**
         * @brief
         * This function returns the name of the role.
         * @detail
         * This must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        robos_roles get_role_name() override;

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
        uint8_t run(const std::array<frame_type, 10> &frames) override;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         */
        uint8_t cleanup() override;
    };
} // namespace r2d2::robos