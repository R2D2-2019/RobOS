#include <robos_role.hpp>

r2d2::robos::robos_role_c::robos_role_c(): core(core) {}

std::array<r2d2::module, 10> r2d2::robos::robos_role_c::get_required_modules() {
    return modules;
}

std::array<r2d2::frame_type , 10> r2d2::robos::robos_role_c::get_required_packets() {
    return packets;
}