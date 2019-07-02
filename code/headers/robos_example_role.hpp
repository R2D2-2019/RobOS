#pragma once

#include <robos_role.hpp>

namespace r2d2::robos {

    class robos_example_role_c : public robos_role_c {
    private:
        enum robos_roles { MANUAL_CONTROL, MOVING_PLATFORM, EXAMPLE_ROLE };

    public:
        robos_example_role_c();

        robos_core::robos_roles get_role_name() override;

        uint8_t run(const std::array<frame_type, 10> &frames) override;

        uint8_t cleanup() override;
    };
} // namespace r2d2::robos