#include <robos_role.hpp>

std::vector<r2d2::frame_type> r2d2::robos::robos_role_c::get_required_modules() {
    return modules;
}

std::vector<r2d2::frame_type> r2d2::robos::robos_role_c::get_required_packets() {
    return packets;
}