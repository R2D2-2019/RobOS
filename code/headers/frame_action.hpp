#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>
#include <timed_request.hpp>

// needed for int_to_str
#include <charconv>

namespace r2d2::robos {
    void int_to_str(unsigned int i, char *str, unsigned int lenght) {
        std::to_chars(str, str + lenght, i);
    }

    class frame_action_c : public timed_request_c {
    protected:
        bool changed = false;

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

        /**
         * process the packet
         */
        virtual void process_packet(frame_s &frame) = 0;

        virtual void reply_to_data() = 0;
    }; // class frame_action_c

    class battery_frame_action_c : public frame_action_c {
    private:
        uint8_t battery_percentage;

        static constexpr char battery_message[10] = "Battery: ";

    public:
        template <typename T>
        battery_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::BATTERY_LEVEL, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto battery_frame =
                frame.as_frame_type<frame_type::BATTERY_LEVEL>();

            if (battery_percentage != battery_frame.percentage) {
                changed = true;
                battery_percentage = battery_frame.percentage;
            }

            // Data recieved, reset timer
            mark_received();
        }

        virtual void reply_to_data() {
            if (changed) {
                frame_display_8x8_character_s frame = {0};
                frame.x = 0;
                frame.y = 0;
                frame.red = 0xFF;
                frame.green = 0xFF;
                frame.blue = 0xFF;

                for (unsigned int i = 0; i < 9; i++) {
                    frame.characters[i] = battery_message[i];
                }
                int_to_str(battery_percentage, frame.characters + 9, 10);

                comm.send(frame);

                changed = false;
            }
        }
    }; // class battery_frame_action_c

    bool operator!=(frame_manual_control_s &lhs, frame_manual_control_s &rhs) {
        return (lhs.brake != rhs.brake) || (lhs.speed != rhs.speed) ||
               (lhs.rotation != rhs.rotation);
    }
    class manual_control_frame_action_c : public frame_action_c {
    private:
        frame_manual_control_s man_control;

    public:
        template <typename T>
        manual_control_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::MANUAL_CONTROL, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto man_control_frame =
                frame.as_frame_type<frame_type::MANUAL_CONTROL>();

            if (man_control != man_control_frame) {
                man_control = man_control_frame;
                changed = true;
            }
            // Data recieved, reset timer
            mark_received();
        }

        virtual void reply_to_data() {
            if (changed) {
                frame_movement_control_s frame;

                frame.brake = man_control.brake;
                frame.rotation = man_control.rotation;
                frame.speed = man_control.speed;

                comm.send(frame);

                changed = false;
            }
        }
    }; // class manual_control_frame_action_c
    class distance_frame_action_c : public frame_action_c {
    private:
        uint16_t distance_mm;

        static constexpr char distance_message[11] = "Distance: ";

    public:
        template <typename T>
        distance_frame_action_c(base_comm_c &comm, T &actions)
            : frame_action_c(comm, frame_type::DISTANCE, actions) {
        }

        void process_packet(frame_s &frame) override {
            auto distance_frame = frame.as_frame_type<frame_type::DISTANCE>();

            if (distance_mm != distance_frame.mm) {
                changed = true;
                distance_mm = distance_frame.mm;
            }

            // Data recieved, reset timer
            mark_received();
        }

        virtual void reply_to_data() {
            if (changed) {
                frame_display_8x8_character_s frame = {0};
                frame.x = 0;
                frame.y = 2;
                frame.red = 0xFF;
                frame.green = 0xFF;
                frame.blue = 0xFF;

                for (unsigned int i = 0; i < 10; i++) {
                    frame.characters[i] = distance_message[i];
                }
                int_to_str(distance_mm, frame.characters + 10, 10);

                comm.send(frame);

                changed = false;
            }
        }
    }; // class distance_frame_action_c
} // namespace r2d2::robos