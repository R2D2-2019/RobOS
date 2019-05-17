#pragma once

#include <base_module.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class timed_request_c {
    private:
        base_comm_c &comm;

        uint_fast32_t start_time;
        const uint_fast32_t timeout;

    protected:
        const frame_type type;

    public:
        timed_request_c(base_comm_c &comm, frame_type type,
                        uint_fast32_t timeout = 100)
            : comm(comm), start_time(0), timeout(timeout), type(type) {
        }

        void mark_received() {
            start_time = 0;
        }

        void request_packet() {
            const auto now_ms =
                static_cast<uint_fast32_t>(hwlib::now_us() / 1000);

            if (start_time == 0 || now_ms - start_time > timeout) {
                comm.request(type);
                start_time = now_ms;
            }
        }
    };
} // namespace r2d2::robos