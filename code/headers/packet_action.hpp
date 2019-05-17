#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>
#include <timed_request.hpp>

namespace r2d2::robos {
    class frame_action_c : public timed_request_c {
    public:
        template <typename T>
        frame_action_c(base_comm_c &comm, frame_type type, T &actions)
            : timed_request_c(comm, type) {
            actions[type] = this;
        }
        template <typename T>
        frame_action_c(base_comm_c &comm, frame_type type, T &actions,
                       uint32_t timeout)
            : timed_request_c(comm, type, timeout) {
            actions[type] = this;
        }

        virtual void process_packet(frame_s &frame) = 0;
    }; // class frame_action_c

    class battery_frame_action_c : public frame_action_c {
    public:
        template <typename T>
        battery_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::BATTERY_LEVEL, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto battery_percentage =
                frame.as_frame_type<frame_type::BATTERY_LEVEL>().percentage;

            hwlib::cout << "battery percentage: "
                        << static_cast<int>(battery_percentage) << "%"
                        << hwlib::endl;
            // Data recieved, reset timer
            mark_received();
        }
    }; // class battery_frame_action_c
    class manual_control_frame_action_c : public frame_action_c {
    public:
        template <typename T>
        manual_control_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::MANUAL_CONTROL, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto distance_frame =
                frame.as_frame_type<frame_type::MANUAL_CONTROL>();

            // Data recieved, reset timer
            mark_received();
        }
    }; // class manual_control_frame_action_c
    class distance_frame_action_c : public frame_action_c {
    public:
        template <typename T>
        distance_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::DISTANCE, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto distance_frame = frame.as_frame_type<frame_type::DISTANCE>();

            // Data recieved, reset timer
            mark_received();
        }
    }; // class distance_frame_action_c
} // namespace r2d2::robos