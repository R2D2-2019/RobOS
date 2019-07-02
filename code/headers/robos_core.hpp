#pragma once
#include <base_module.hpp>
#include <esp_32.hpp>
#include <frame_handler.hpp>
#include <frame_types.hpp>
#include <hwlib.hpp>
#include <ringbuffer.hpp>
#include <robos_role.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {

    enum robos_state { WAIT, INITROLE, RUNROLE, UPDATEMODULES, SHUTDOWN };

    enum robos_roles { MANUAL_CONTROL, MOVING_PLATFORM, EXAMPLE_ROLE };

    class robos_core_c : public base_module_c {
    private:
        uint_fast16_t id;
        r2d2::module mod_list[20];
        robos_state state;
        robos_roles role;
        robos_role_c *current_role;
        r2d2::communication::esp_32_c &esp;
        std::array<timed_request_c, frame_type::COUNT> requests = {};

    public:
        robos_core_c(base_comm_c &comm, r2d2::communication::esp_32_c &esp);
        std::vector<frame_type> outgoing_frame_buffer;
        void process() override;
        int get_identity_packets();
        int run();
        int wait_command();
        int init_role();
        int run_role();
        int update_modules();
        int shutdown_robos();
    };
} // namespace r2d2::robos