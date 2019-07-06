#include <ostream>

#define CATCH_CONFIG_MAIN
#include <array>
#include <catch.hpp>
#include <manual_control_role.hpp>
#include <moving_platform_role.hpp>
#include <robos_example_role.hpp>

/**
 * @Brief
 * Test cases for RobOS
 * @detail
 * Not all functionality of robOS can be tested,
 * Because of comm.hpp requiring makefile.due
 */

TEST_CASE("Manual control role", "[robos role]") {
    r2d2::robos::manual_control_role_c manual_role;

    SECTION("Calling cleanup function of role") {

        REQUIRE(manual_role.cleanup() == 0);
    }

    SECTION("Calling run function of role") {

        REQUIRE(manual_role.get_role_name() ==
                r2d2::robos::robos_roles::MANUAL_CONTROL);
    }

    SECTION("Getting required modules of role") {
        std::array<r2d2::frame_id, 10> modules =
            manual_role.get_required_modules();
        REQUIRE(modules[0] ==
                static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM));
        REQUIRE(modules[1] ==
                static_cast<r2d2::frame_type>(r2d2::module::MANUAL_CONTROL));
    }

    SECTION("Getting required packets of role") {
        std::array<r2d2::frame_type, 10> packets =
            manual_role.get_required_packets();
        REQUIRE(packets[0] == r2d2::frame_type::MANUAL_CONTROL_SLIDER);
        REQUIRE(packets[1] == r2d2::frame_type::MANUAL_CONTROL_JOYSTICK);
        REQUIRE(packets[2] == r2d2::frame_type::MANUAL_CONTROL_BUTTON);
    }
}

TEST_CASE("Moving platform role", "[robos role]") {
    r2d2::robos::moving_platform_role_c platform_role;

    SECTION("Calling cleanup function of role") {

        REQUIRE(platform_role.cleanup() == 0);
    }

    SECTION("Calling run function of role") {

        REQUIRE(platform_role.get_role_name() ==
                r2d2::robos::robos_roles::MOVING_PLATFORM);
    }

    SECTION("Getting required modules of role") {
        std::array<r2d2::frame_id, 10> modules =
            platform_role.get_required_modules();
        REQUIRE(modules[0] ==
                static_cast<r2d2::frame_type>(r2d2::module::MOVING_PLATFORM));
    }

    SECTION("Getting required packets of role") {
        std::array<r2d2::frame_type, 10> packets =
            platform_role.get_required_packets();
        REQUIRE(packets[0] == r2d2::frame_type::MOVEMENT_CONTROL);
    }
}

TEST_CASE("Robos example role", "[robos role]") {
    r2d2::robos::robos_example_role_c example_role;

    SECTION("Calling cleanup function of role") {

        REQUIRE(example_role.cleanup() == 0);
    }

    SECTION("Calling run function of role") {

        REQUIRE(example_role.get_role_name() ==
                r2d2::robos::robos_roles::EXAMPLE_ROLE);
    }

    SECTION("Getting required modules of role") {
        std::array<r2d2::frame_id, 10> modules =
            example_role.get_required_modules();
        REQUIRE(modules[0] == static_cast<r2d2::frame_type>(r2d2::module::LED));
        REQUIRE(modules[1] ==
                static_cast<r2d2::frame_type>(r2d2::module::BUTTON));
    }

    SECTION("Getting required packets of role") {
        std::array<r2d2::frame_type, 10> packets =
            example_role.get_required_packets();
        REQUIRE(packets[0] == r2d2::frame_type::BUTTON_STATE);
    }
}