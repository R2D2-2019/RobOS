#pragma once

#include <base_comm.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class display_ostream_c : public hwlib::ostream {
    private:
        const uint8_t cursor_id;
        hwlib::color color;

        base_comm_c &comm;
        frame_display_8x8_character_via_cursor_s text_frame;
        uint8_t text_index = 0;
        frame_cursor_position_s position_frame;

        void send_color() {
            frame_cursor_color_s frame;

            frame.cursor_id = cursor_id;
            frame.red = color.red;
            frame.green = color.green;
            frame.blue = color.blue;
        }

    public:
        display_ostream_c(base_comm_c &comm, claimed_display_cursor cursor,
                          hwlib::color color, uint8_t x, uint8_t y)
            : hwlib::ostream(),
              cursor_id(static_cast<uint8_t>(cursor)),
              color(color),
              comm(comm) {
            text_frame.cursor_id = cursor_id;

            position_frame.cursor_id = cursor_id;
            position_frame.cursor_x = x;
            position_frame.cursor_y = y;

            send_color();
        }
        virtual void flush() override {

            text_frame.characters[text_index] = '\0';
            comm.send(position_frame);
            comm.send(text_frame);
            text_index = 0;
        }

        virtual void putc(char c) override {
            text_frame.characters[text_index] = c;
            text_index++;
        }
        /// set the color to x
        const void set_color(hwlib::color x) {
            if (color == x) {
                // no need to send frame
                return;
            }
            color = x;
            send_color();
        }
        /// return the current color
        const hwlib::color &get_color() const {
            return color;
        }
    };

} // namespace r2d2::robos