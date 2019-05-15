

#include <hwlib.hpp>

#include <comm.hpp>
#include <led_module.hpp>
#include <module.hpp>
#include <test_module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    r2d2::comm_c comm;
    auto robos = r2d2::robos::module_c(comm);

    r2d2::comm_c comm2;
    auto test_mod = r2d2::test_module::module_c(comm2);

    r2d2::comm_c comm3;
    auto d6 = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto led = r2d2::led::module_c(comm3, d6);

    for (;;) {
        robos.process();
        test_mod.process();
        led.process();
        hwlib::wait_ms(100);
    }
}