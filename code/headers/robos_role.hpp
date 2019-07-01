#pragma once

#include <frame_types.hpp>
#include <stdint.h>
#include <vector>

namespace r2d2::robos {

    class robos_role_c {
    protected:
        std::vector<frame_type> modules;
        std::vector<frame_type> packets;

    public:
        /**
         * @brief
         * Constructor robos_role_c
         *
         * The default constructor is empty.
         */
        robos_role_c(){};

        /**
         * @brief
         * This function returns the name of the role.
         * @detail
         * This must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        virtual char *get_role_name() = 0;

        /**
         * @brief
         * This function returns a vector of the needed modules
         * @detail
         * This function returns the modules that are required
         * to process this role in the run function.
         */
        virtual std::vector<frame_type> get_required_modules();

        /**
         * @brief
         * This function returns a vector of the needed packets
         * @detail
         * This function returns the packets that are required
         * to process this role in the run function.
         */
        virtual std::vector<frame_type> get_required_packets();

        /**
         * @brief
         * This function handles the tasks of the role.
         *
         * @param std::vector<frame_type>: frames
         * The required frames to process this role.
         * @detail
         * This function will receive data of certain modules and
         * send the data to other modules if requirements are met.
         * This function must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        virtual uint8_t run(std::vector<frame_type> &frames) = 0;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         */
        virtual uint8_t cleanup() = 0;
    };
} // namespace r2d2::robos