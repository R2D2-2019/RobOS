#pragma once

#include <frame_types.hpp>
#include <stdint.h>
#include <vector>

namespace r2d2::robos {

    class robos_role_c {
    private:
        std::vector<frame_type> modules;
        std::vector<frame_type> packets;

    public:
        robos_role_c(){};
        virtual char *get_role_name() = 0;
        virtual std::vector<frame_type> get_required_modules();
        virtual std::vector<frame_type> get_required_packets();
        virtual uint8_t run(std::vector<frame_type> &frames) = 0;
        virtual uint8_t cleanup() = 0;
    };
} // namespace r2d2::robos