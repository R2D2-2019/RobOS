#include <manual_control_role.hpp>

r2d2::robos::manual_control_role_c::manual_control_role_c() {
    robos_role_c::modules[0] = static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM);
    robos_role_c::modules[1] = static_cast<r2d2::frame_type>(r2d2::module::MANUAL_CONTROL);
    robos_role_c::packets[0] = r2d2::frame_type::MANUAL_CONTROL_SLIDER;
	robos_role_c::packets[1] = r2d2::frame_type::MANUAL_CONTROL_JOYSTICK;
	robos_role_c::packets[2] = r2d2::frame_type::MANUAL_CONTROL_BUTTON;
}

r2d2::robos::robos_roles r2d2::robos::manual_control_role_c::get_role_name() {
    return robos_roles::MANUAL_CONTROL;
}

    r2d2::robos::manual_control_role_c::process_movement_control_speed(const frame_s &frame) {
        auto data = frame.as_frame_type<frame_type::MANUAL_CONTROL_SLIDER>();

        // convert to moving platform
        // slider id 0 is left peddel and slider id 1 is right peddel
        if (data.slider_id == 0) {
            brake = true;
            speed = 0;
        } else {
            brake = false;
            if (forward == true) {
                speed = data.value;
            } else {
                speed = -data.value;
            }
        }
        flag_for_send = 1;
        // Data recieved, reset timer
        manual_control_request_speed.mark_received();
    }

    void r2d2::robos::manual_control_role_c::process_movement_control_steer(const frame_s &frame) {
        auto data = frame.as_frame_type<frame_type::MANUAL_CONTROL_JOYSTICK>();

        // convert to moving platform
        steering_angle = data.value_x;
        flag_for_send = 1;
        // Data recieved, reset timer
        manual_control_request_steer.mark_received();
    }

    void r2d2::robos::manual_control_role_c::process_movement_control_direction(const frame_s &frame) {
        auto data = frame.as_frame_type<frame_type::MANUAL_CONTROL_BUTTON>();
        hwlib::cout << " button pressed: " << data.button_id << "\n";
        if (data.button_id == 0 && data.value == true) {
            forward = true;
        } else if (data.button_id == 3 && data.value == true) {
            forward = false;
        }

        manual_control_request_direction.mark_received();
    }

uint8_t r2d2::robos::manual_control_role_c::run(
    const std::array<r2d2::frame_type, 10> &frames) {

    if (frames.size() > 0) {
		for(int i = 0; i < frames.size(); i++){
			switch (frames[i].type) {
			case frame_type::MANUAL_CONTROL_SLIDER:
				process_movement_control_speed(frames[i]);
				break;
			case frame_type::MANUAL_CONTROL_JOYSTICK:
				process_movement_control_steer(frames[i]);
				break;
			case frame_type::MANUAL_CONTROL_BUTTON:
				process_movement_control_direction(frames[i]);
				break;
			default:
				break;
			}
		}
    }
	
	if (flag_for_send) {
		flag_for_send = 0;

		// send frame to moving platform
		frame_movement_control_s movement;

		movement.brake = brake;
		movement.rotation = steering_angle;
		movement.speed = speed;
		
		//r2d2::robos::robos_role_c::get_outgoing_frames[0] = movement;
		//comm.send(movement);
	}

    return 0;
}

uint8_t r2d2::robos::manual_control_role_c::cleanup() {


    return 0;
}