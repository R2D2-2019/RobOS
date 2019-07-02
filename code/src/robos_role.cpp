#include <robos_role.hpp>

r2d2::robos::robos_role_c::robos_role_c(){}

std::array<r2d2::frame_type, 10> r2d2::robos::robos_role_c::get_outgoing_frames(){
    return outgoing_frame_data;
}

std::array<r2d2::frame_id, 10> r2d2::robos::robos_role_c::get_required_modules() {
    return modules;
}

std::array<r2d2::frame_type , 10> r2d2::robos::robos_role_c::get_required_packets() {
    return packets;
}