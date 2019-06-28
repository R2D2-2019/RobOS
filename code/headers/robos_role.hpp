#pragma once

#include <stdint.h>
#include <vector>
#include <frame_action.hpp>

namespace r2d2::robos {
    class robos_role {
    public:
        robos_role(std::vector<frame_type> &frames);
        virtual char *get_role_name() = 0;
        virtual std::vector<frame_type> get_required_modules();
        virtual std::vector<frame_type> get_required_packets();
        virtual uint8_t run(std::vector<frame_type> &frames) = 0;
        virtual uint8_t cleanup() = 0;
    };
} // namespace r2d2::robos