#pragma once
#include <base_module.hpp>
#include <frame_types.hpp>
#include <robos_role.hpp>

namespace r2d2::robos {

    enum robos_state { WAIT, INITROLE, RUNROLE, UPDATEMODULES, SHUTDOWN };

    enum robos_roles { MANUAL_CONTROL, MOVING_PLATFORM, EXAMPLE_ROLE };

    class robos_core_c : public base_module_c {
    private:
        uint_fast16_t id;
        int mod_list[20];
        robos_state state = WAIT;
        robos_roles role = MANUAL_CONTROL;
        robos_role_c *robos_role;

    public:
        std::vector<frame_type> outgoing_frame_buffer;
        void process() override;
        robos_core_c(base_comm_c &comm);
        int get_identity_packets();
        int run();
        int wait_command();
        int init_role();
        int run_role();
        int update_modules();
        int shutdown_robos();
    };
} // namespace r2d2::robos