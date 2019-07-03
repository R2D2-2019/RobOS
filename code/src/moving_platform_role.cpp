#include <moving_platform_role.hpp>

r2d2::robos::moving_platform_role_c::moving_platform_role_c() {
    robos_role_c::modules[1] =
        static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM);
    // robos_role_c::packets[0] = r2d2::frame_type::;
}

r2d2::robos::robos_roles r2d2::robos::moving_platform_role_c::get_role_name() {
    return robos_roles::MOVING_PLATFORM;
}

uint8_t r2d2::robos::moving_platform_role_c::run(ringbuffer_c<frame_s, 32> &ringbuffer) {

    while (!ringbuffer.empty()) {
        auto frame = ringbuffer.copy_and_pop();
        r2d2::robos::robos_role_c::outgoing_frame_data.push(frame);
    }

    return 0;
}

uint8_t r2d2::robos::moving_platform_role_c::cleanup() {

    return 0;
}