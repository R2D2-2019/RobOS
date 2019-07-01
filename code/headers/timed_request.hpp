#pragma once

#include <base_module.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    /**
     * this class makes it possible to request a frame and set a timer to
     * re-send the request if the respons isn't received before the timeout.
     */
    class timed_request_c {
    private:
        uint_fast32_t start_time;
        uint_fast32_t timeout;
        frame_type type;
        base_comm_c *comm;

    public:
        timed_request_c()
            : start_time(0), timeout(0), type(frame_type::NONE), comm(nullptr) {
        }

        timed_request_c(base_comm_c *comm, frame_type type,
                        uint_fast32_t timeout = 100)
            : start_time(0), timeout(timeout), type(type), comm(comm) {
        }

        timed_request_c &operator=(timed_request_c rhs) {
            comm = rhs.comm;
            type = rhs.type;
            timeout = rhs.timeout;
            start_time = 0;

            return *this;
        }

        /**
         * mark the request as received. The next time request_packet is called
         * after this, a new request will be sent
         */
        void mark_received() {
            start_time = 0;
        }

        /**
         * send a request packet if there is not send a packet already
         * This function also sends a new request if the request was not
         * received before the timeout.
         */
        void request_packet() {
            const auto now_ms =
                static_cast<uint_fast32_t>(hwlib::now_us() / 1000);

            if (start_time == 0 || now_ms - start_time > timeout) {
                comm->request(type);
                start_time = now_ms;
            }
        }

        const frame_type get_type() const {
            return type;
        }
    };
} // namespace r2d2::robos