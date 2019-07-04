#include <manual_control_role.hpp>

r2d2::robos::manual_control_role_c::manual_control_role_c() {
    robos_role_c::modules[0] =
        static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM);
    robos_role_c::modules[1] =
        static_cast<r2d2::frame_type>(r2d2::module::MANUAL_CONTROL);
    robos_role_c::packets[0] = r2d2::frame_type::MANUAL_CONTROL_SLIDER;
    robos_role_c::packets[1] = r2d2::frame_type::MANUAL_CONTROL_JOYSTICK;
    robos_role_c::packets[2] = r2d2::frame_type::MANUAL_CONTROL_BUTTON;
}

r2d2::robos::robos_roles r2d2::robos::manual_control_role_c::get_role_name() {
    return robos_roles::MANUAL_CONTROL;
}

void r2d2::robos::manual_control_role_c::process_movement_control_speed(
    const frame_manual_control_slider_s &frame) {

    // convert to moving platform
    // slider id 0 is left peddel and slider id 1 is right peddel
    if (frame.slider_id == 0) {
        brake = true;
        speed = 0;
    } else {
        brake = false;
        if (forward == true) {
            speed = frame.value;
        } else {
            speed = -frame.value;
        }
    }
    flag_for_send = 1;
    // Data recieved, reset timer
    // manual_control_request_speed.mark_received();
}

void r2d2::robos::manual_control_role_c::process_movement_control_steer(
    const frame_manual_control_joystick_s &frame) {

    // convert to moving platform
    steering_angle = frame.value_x;
    flag_for_send = 1;
    // Data recieved, reset timer
    // manual_control_request_steer.mark_received();
}

void r2d2::robos::manual_control_role_c::process_movement_control_direction(
    const frame_manual_control_button_s &frame) {
    if (frame.button_id == 0 && frame.value == true) {
        forward = true;
    } else if (frame.button_id == 3 && frame.value == true) {
        forward = false;
    }

    // manual_control_request_direction.mark_received();
}

uint8_t r2d2::robos::manual_control_role_c::run(
    ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer) {

    while (!ringbuffer.empty()) {
        std::array<uint8_t, 256> hackframe = ringbuffer.copy_and_pop();
        // To get the frame back:
        // frame_type type = static_cast<frame_type>(buffer[0]);
        // frame_button_state_s state =

        // *(reinterpret_cast<frame_button_state_s>(buffer[1]))
        frame_type type = static_cast<frame_type>(hackframe[0]);
        switch (type) {
        case frame_type::MANUAL_CONTROL_SLIDER: {
            frame_manual_control_slider_s frame1 =
                *(reinterpret_cast<frame_manual_control_slider_s *>(
                    &hackframe[1]));
            process_movement_control_speed(frame1);
            break;
        }
        case frame_type::MANUAL_CONTROL_JOYSTICK: {
            frame_manual_control_joystick_s frame2 =
                *(reinterpret_cast<frame_manual_control_joystick_s *>(
                    &hackframe[1]));
            process_movement_control_steer(frame2);
            break;
        }
        case frame_type::MANUAL_CONTROL_BUTTON: {
            frame_manual_control_button_s frame3 =
                *(reinterpret_cast<frame_manual_control_button_s *>(
                    &hackframe[1]));
            process_movement_control_direction(frame3);
            break;
        }
        case frame_type::NONE:
            break;
        default:
            break;
        }
    }

    if (flag_for_send) {
        flag_for_send = 0;

        // send frame to moving platform
        frame_movement_control_s movement;

        movement.brake = brake;
        movement.rotation = steering_angle;
        movement.speed = speed;
        uint8_t buffer[256];
        buffer[0] = frame_type::MOVEMENT_CONTROL;
        for (int i = 0; i < movement.length; i++) {
            buffer[i + 1] = movement.data[i];
        }
        r2d2::robos::robos_role_c::outgoing_frame_data.push(buffer);
        // comm.send(movement);
    }

    return 0;
}

uint8_t r2d2::robos::manual_control_role_c::cleanup() {

    return 0;
}