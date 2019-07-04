#include <robos_core.hpp>

namespace r2d2::robos {
    robos_core_c::robos_core_c(base_comm_c &comm,
                               r2d2::communication::esp_32_c &esp)
        : base_module_c(comm), esp(esp) {
        comm.configure(r2d2::module::NONE, {r2d2::frame_type::ALL});
    }

    void robos_core_c::process() {
        bool end = false;
        int error_code;
        ringbuffer_c<std::array<uint8_t, 256>, 32> ringbuffer;

        while (!end) {
            // esp comes here
            // Set out all polling requests
            for (auto &request : requests) {
                if (request.get_type() != frame_type::NONE) {
                    request.request_packet();
                }
            }

            // process received frames
            while (comm.has_data()) {
                auto frame = comm.get_data();
                // This module doesn't handle requests
                if (frame.request) {
                    continue;
                }

                uint8_t buffer[256];

                // To get the frame back:
                // frame_type type = static_cast<frame_type>(buffer[0]);
                // frame_button_state_s state =
                // *(reinterpret_cast<frame_button_state_s>(buffer[1]))

                buffer[0] = static_cast<uint8_t>(frame.type);
                for (int i = 0; i < frame.length; i++) {
                    buffer[i + 1] = frame.data[i];
                }

                ringbuffer.push(buffer);
                // process the received packet using the appropriate
                // frame-handler
                // handler.process(frame);

                // Data recieved, reset timer
                auto &request = requests[frame.type];
                if (request.get_type() != frame_type::NONE) {
                    request.mark_received();
                }
            }

            switch (robos_core_c::state) {

            case robos_state::WAIT:
                error_code = robos_core_c::wait_command();
                break;
            case robos_state::INITROLE:
                error_code = robos_core_c::init_role();
                break;
            case robos_state::RUNROLE:
                error_code = robos_core_c::run_role(ringbuffer);
                break;
            case robos_state::UPDATEMODULES:
                error_code = robos_core_c::update_modules();
                break;
            case robos_state::SHUTDOWN:
                error_code = robos_core_c::shutdown_robos();
                end = true;
            }
            end = true;
        }
    };

    int robos_core_c::wait_command() {
        robos_core_c::state = robos_state::INITROLE;

        // potentially choose role here
        return 0;
    };

    int robos_core_c::init_role() {
        switch (robos_core_c::role) {
        case robos_roles::MANUAL_CONTROL:
            // auto manual_control_role = robos_role_c();
            // robos_core_c::robos role = manual_control_role;
            break;
        case robos_roles::MOVING_PLATFORM:
            // auto moving_platform_role = robos_role_c();
            // robos_core_c::robos role = moving_platform;
            break;
        case robos_roles::EXAMPLE_ROLE:
            // auto moving_platform_role = robos_role_c();
            // robos_core_c::robos role = moving_platform;
            break;
        }

        return 0;
    };

    int robos_core_c::run_role(ringbuffer_c<uint8_t[256], 32> &ringbuffer) {
        robos_core_c::current_role->run(ringbuffer);

        ringbuffer = robos_core_c::current_role->get_outgoing_frames();

        while (!ringbuffer.empty()) {
            std::array<uint8_t, 256> hackframe = ringbuffer.copy_and_pop();
            frame_type type = static_cast<frame_type>(hackframe[0]);
            if (type == frame_type::EXTERNAL) {
                auto external_frame = hackframe;
                esp.send(hackframe);
            } else {
                comm.send(hackframe);
            }
        }

        r2d2::frame_external_s recv_external_frame;
        bool recv = esp.receive(recv_external_frame);

        if (recv) {
            frame_s nframe;
            nframe.data = recv_external_frame.data;
            nframe.length = recv_external_frame.length;
            nframe.type = recv_external_frame.type;
            nframe.request = false;
            ringbuffer.push(nframe);
        }

        return 0;
    };

    int robos_core_c::shutdown_robos() {
        robos_core_c::current_role->cleanup();
        return 0;
    };

    int robos_core_c::update_modules() {
        ringbuffer_c<std::array<uint8_t, 256>, 32> ringbuffer;
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