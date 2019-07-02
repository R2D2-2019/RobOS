#include <hwlib.hpp>

#include <comm.hpp>
#include <module.hpp>
#include <test_module.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    /// connect to esp
    auto ss = hwlib::target::pin_out(hwlib::target::pins::d4);
    auto hs = hwlib::target::pin_in(hwlib::target::pins::d5);
    auto spi_bus =
        hwlib::target::hwspi(1, hwlib::target::hwspi::SPI_MODE::SPI_MODE1, 42);

    auto esp = r2d2::communication::esp_32_c(spi_bus, ss, hs);
    r2d2::comm_c comm;
    auto robos = r2d2::robos::module_c(comm, esp);

    r2d2::comm_c comm2;
    auto power = r2d2::test_module::module_c(comm2);

    for (;;) {
        robos.process();
        power.process();
        hwlib::wait_ms(150);
    }
}