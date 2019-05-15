#include "hwlib.hpp"

#include <module.hpp>
#include <comm.hpp>

int main(void) {
  // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    r2d2::comm_c comm;

    auto robos = r2d2::robos::module_c(comm);

    for (;;) {
        robos.process();

        hwlib::wait_ms(1);
    }
}