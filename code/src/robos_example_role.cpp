#include <robos_example_role.hpp>

r2d2::robos::robos_example_role_c::robos_example_role_c() {
    robos_role_c::modules[0] = static_cast<r2d2::frame_type>(r2d2::module::LED);
    robos_role_c::modules[1] =
        static_cast<r2d2::frame_type>(r2d2::module::BUTTON);
    robos_role_c::packets[0] = r2d2::frame_type::BUTTON_STATE;
}

r2d2::robos::robos_roles r2d2::robos::robos_example_role_c::get_role_name() {
    return robos_roles::EXAMPLE_ROLE;
}

uint8_t r2d2::robos::robos_example_role_c::run(
    const std::array<r2d2::frame_type, 10> &frames) {

    if (frames.size() > 0) {
        frame_activity_led_state_s led_state;
        led_state.state = frames[0];

        // r2d2::robos::robos_role_c::get_outgoing_frames[0] = led_state;
    }

    return 0;
}

uint8_t r2d2::robos::robos_example_role_c::cleanup() {
    // frame_activity_led_state_s led_state;

    return 0;
}