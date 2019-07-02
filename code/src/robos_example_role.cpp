#include <robos_example_role.hpp>

r2d2::robos::robos_example_role_c::robos_example_role_c() : name(EXAMPLE_ROLE) {
    robos_role_c::modules[0] = r2d2::module::LED;
    robos_role_c::modules[1] = r2d2::module::BUTTON;
    robos_role_c::packets[0] = r2d2::frame_type::BUTTON_STATE;
}

r2d2::robos::robos_core_c::robos_roles
r2d2::robos::robos_example_role_c::get_role_name() {
    return name;
}

uint8_t
r2d2::robos::robos_example_role_c::run(const std::vector<frame_type> &frames) {

    if (frames.size > 0) {
        frame_activity_led_state_s led_state;
        led_state.state = frames[0];

        robos_role_c::core.outgoing_frame_buffer[0] = led_state;
    }

    return 0;
}

uint8_t r2d2::robos::robos_example_role_c::cleanup() {
    frame_activity_led_state_s led_state;
    robos_role_c::core.outgoing_frame_buffer[0] = led_state;

    return 0;
}