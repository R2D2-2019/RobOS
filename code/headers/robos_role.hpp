#pragma once

#include <array>
#include <base_module.hpp>
#include <frame_types.hpp>
#include <ringbuffer.hpp>
#include <robos_enums.hpp>
#include <stdint.h>

namespace r2d2::robos {

    class robos_role_c {
    protected:
        std::array<frame_id, 10> modules{};
        std::array<frame_type, 10> packets{};

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
         *
         * @return enum role of enum class robos_roles
         */
        virtual robos_roles get_role_name() = 0;

        /**
         * @brief
         * This function returns an array of the needed modules.
         * @detail
         * This function returns the modules that are required
         * to process this role in the run function.
         * 
         * @return array of frame_id(s)
         */
        virtual std::array<r2d2::frame_id, 10> get_required_modules();

        /**
         * @brief
         * This function returns an array of the needed packets.
         * @detail
         * This function returns the packets that are required
         * to process this role in the run function.
         * 
         * @return array of frame_type(s)
         */
        virtual std::array<frame_type, 10> get_required_packets();

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
        virtual uint8_t
            run(ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer,
                base_comm_c &comm) = 0;

        /**
         * @brief
         * This function resets modules and unnecessary objects
         * to make robOS ready for a new role.
         * 
         * @return uint8_t
         */
        virtual uint8_t cleanup() = 0;
    };
} // namespace r2d2::robos