#pragma once

#include <display_ostream.hpp>
#include <frame_action.hpp>
#include <hwlib.hpp>

namespace r2d2::robos {
    class temperature_frame_action_c
        : public frame_action_c<frame_type::TEMPERATURE> {
    private:
        display_ostream_c ostream;
        static constexpr char temperature_message[11] = "Obj temp: ";

    public:
        temperature_frame_action_c(base_comm_c &comm, frame_s &frame);

        virtual void reply_to_data() override;
    }; // class temperature_frame_action_c
} // namespace r2d2::robos