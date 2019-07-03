#include <moving_platform_role.hpp>

r2d2::robos::moving_platform_role_c::manual_control_role_c() {
    robos_role_c::modules[1] = static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM);
    //robos_role_c::packets[0] = r2d2::frame_type::;

}

r2d2::robos::robos_roles r2d2::robos::moving_platform_role_c::get_role_name() {
    return robos_roles::MOVING_PLATFORM;
}

uint8_t r2d2::robos::moving_platform_role_c::run(
    const std::array<r2d2::frame_type, 10> &frames) {

    if (frames.size() > 0) {
		//r2d2::robos::robos_role_c::get_outgoing_frames[0] = frames[0];
    }

    return 0;
}

uint8_t r2d2::robos::moving_platform_role_c::cleanup() {


    return 0;
}