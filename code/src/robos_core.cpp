#include <robos_core.hpp>

namespace r2d2::robos {
    robos_core_c::robos_core_c(base_comm_c &comm) : base_module_c(comm) {
        comm.configure(r2d2::module::NONE, {r2d2::frame_type::ALL});
    }

    void robos_core_c::process() {
        bool end = false;
        int error_code;
        while (!end) {
            switch (robos_core_c::state) {
            case WAIT:
                error_code = robos_core_c::wait_command();
                break;
            case INITROLE:
                error_code = robos_core_c::init_role();
                break;
            case RUNROLE:
                error_code = robos_core_c::run_role();
                break;
            case UPDATEMODULES:
                error_code = robos_core_c::update_modules();
                break;
            case SHUTDOWN:
                error_code = robos_core_c::shutdown_robos();
                end = true;
            }
            end = true;
        }
    };

    int robos_core_c::wait_command() {
        robos_core_c::state = INITROLE;
        // potentially choose role here
        return 0;
    };

    int robos_core_c::init_role() {
        switch (robos_core_c::role) {
        case MANUAL_CONTROL:
            // auto manual_control_role = robos_role_c();
            // robos_core_c::robos role = manual_control_role;
            break;
        case MOVING_PLATFORM:
            // auto moving_platform_role = robos_role_c();
            // robos_core_c::robos role = moving_platform;
            break;
        case EXAMPLE_ROLE:
            // auto moving_platform_role = robos_role_c();
            // robos_core_c::robos role = moving_platform;
            break;
        }

        return 0;
    };

    int robos_core_c::run_role() {
        const std::vector<frame_type> test_frame;
        robos_core_c::current_role->run(test_frame);
        // ringbuffer_c robos_core_c::current_role->getoutgoingframes();
        ringbuffer_c<frame_s, 32> ringbuffer;
        while (!ringbuffer.empty()) {
            auto frame = ringbuffer.copy_and_pop();
            comm.send(frame);
        }
        return 0;
    };

    int robos_core_c::shutdown_robos() {
        robos_core_c::current_role->cleanup();
        return 0;
    };

    int robos_core_c::update_modules() {
        ringbuffer_c<frame_s, 32> ringbuffer;
        comm.request(IDENTITY);
        hwlib::wait_ms(1000);
        int mod_list_counter = 0;
        while (comm.has_data()) {
            auto frame = comm.get_data();
            if (frame.type == IDENTITY) {
                const auto data = frame.as_frame_type<frame_type::IDENTITY>();
                mod_list[mod_list_counter] = data.type;
            } else {
            }
            mod_list_counter += 1;
        }
        return 0;
    };

} // namespace r2d2::robos