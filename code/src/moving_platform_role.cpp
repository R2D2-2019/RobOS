#include <moving_platform_role.hpp>

r2d2::robos::moving_platform_role_c::moving_platform_role_c() {
    robos_role_c::modules[1] =
        static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM);
}

r2d2::robos::robos_roles r2d2::robos::moving_platform_role_c::get_role_name() {
    return robos_roles::MOVING_PLATFORM;
}

uint8_t r2d2::robos::moving_platform_role_c::run(
    ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer, base_comm_c &comm) {

    while (!ringbuffer.empty()) {
        auto frame = ringbuffer.copy_and_pop();

    }

    return 0;
}

uint8_t r2d2::robos::moving_platform_role_c::cleanup() {

    return 0;
}