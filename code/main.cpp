

#include <hwlib.hpp>

#include <comm.hpp>
// #include <led_module.hpp>
#include <module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    r2d2::comm_c comm;
    auto move_os = r2d2::robos::module_c(comm);

    for (;;) {
        move_os.process();
        hwlib::wait_ms(100);
    }
}