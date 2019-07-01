#include <hwlib.hpp>

#include <comm.hpp>
#include <module.hpp>
#include <test_module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    r2d2::comm_c comm;
    auto robos = r2d2::robos::module_c(comm);

    r2d2::comm_c comm2;
    auto power = r2d2::test_module::module_c(comm2);

    for (;;) {
        robos.process();
        power.process();
        hwlib::wait_ms(150);
    }
}