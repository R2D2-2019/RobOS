#pragma once

#include <robos_role.hpp>

namespace r2d2::robos {

    class robos_example_role_c : public robos_role_c {
    private:
        enum name;

    public:
        robos_example_role_c();

        robos_core::robos_roles get_role_name() override;

        uint8_t run(const std::vector<frame_type> &frames) override;

        uint8_t cleanup() override;
    };
} // namespace r2d2::robos