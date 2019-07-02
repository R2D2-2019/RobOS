#pragma once

#include <frame_types.hpp>
#include <robos_enums.hpp>
#include <stdint.h>
#include <array>

namespace r2d2::robos {

    class robos_role_c {
    protected:
        std::array<frame_id, 10> modules{};
        std::array<frame_type, 10> packets{};
        std::array<frame_type, 10> outgoing_frame_data{};

    public:
        /**
         * @brief
         * Constructor robos_role_c
         *
         * The default constructor is empty.
         */
        robos_role_c();

        /**
         * @brief
         * This function returns the name of the role.
         * @detail
         * This must be overridden by the child class
         * of the abstract class robos_role_c.
         */
        virtual robos_roles get_role_name() = 0;
        
        /**
         * @brief
         * This function returns an array of the needed modules
         * @detail
         * This function returns all the frames that need to be send on the can bus.
         */
        virtual std::array<r2d2::frame_type, 10> get_outgoing_frames();

        /**
         * @brief
         * This function returns an array of the needed modules
         * @detail
         * This function returns the modules that are required
         * to process this role in the run function.
         */
        virtual std::array<r2d2::frame_id, 10> get_required_modules();

        /**
         * @brief
         * This function returns an array of the needed packets
         * @detail
         * This function returns the packets that are required
         * to process this role in the run function.
         */
        virtual std::array<frame_type, 10> get_required_packets();

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
        virtual uint8_t run(const std::array<frame_type, 10> &frames) = 0;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         */
        virtual uint8_t cleanup() = 0;
    };
} // namespace r2d2::robos