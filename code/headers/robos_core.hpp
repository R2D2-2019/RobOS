#pragma once
#include <array>
#include <base_module.hpp>
#include <esp_32.hpp>
#include <frame_handler.hpp>
#include <frame_types.hpp>
#include <hwlib.hpp>
#include <ringbuffer.hpp>
#include <robos_role.hpp>
#include <timed_request.hpp>

#include <robos_enums.hpp>

namespace r2d2::robos {

    class robos_core_c : public base_module_c {
    private:
        uint_fast16_t id;
        r2d2::module mod_list[20];
        bool shutdown;
        int error_code;
        ringbuffer_c<std::array<uint8_t, 256>, 32> ringbuffer;
        robos_state state;
        robos_roles role;
        robos_role_c *current_role;
        r2d2::communication::esp_32_c &esp;
        std::array<timed_request_c, frame_type::COUNT> requests = {};

    public:
        /**
         * @brief
         * Constructor for the robos_core_c class
         * @detail
         * Constructor which requires a base_comm_c object reference and a
         * esp_32_c object reference. In the constructor base_module_c is
         * initialized with the base_comm_c object reference.
         */
        robos_core_c(base_comm_c &comm, r2d2::communication::esp_32_c &esp);

        /**
         * @brief
         * Init function to set the initial state of robos_core
         * @detail
         * Init function that take a robos_state enum class as a parameter and
         * sets robos_core_c::state to it.
         * @param init state : robos_state
         * init_state parameter to set robos_core_c state.
         */
        void init(robos_state init_state);

        /**
         * @brief
         * Overriden function of the base_module_c parent class that is called
         * to run the robos module.
         * @detail
         * The main run function of this class with a continuous loop which
         * contains a state machine. The state machine keeps track in which
         * state robos currently is and what functions to call depending on the
         * state. Each state has its own function to execute. The states are
         * represented in an enum class "robos_states" which are located in
         * robos_enums.hpp. The main function of these states are explained in
         * these accompanying function. In the main loop comm is used to listen
         * for and filter packets from the can bus. Depending on the frame type
         * these packets are then either send to current_role for use there or
         * to change state. Eventually these can also be send over external come
         * once this module works and implementation has been realized.
         */
        void process() override;

        /**
         * @brief
         * Function that waits for commands from SMM.
         * @detail
         * State function that is called when robOS current state is the wait
         * state, wherein the function continuously waits for command packets
         * from Swarm Management once that module has been realized and
         * implemented. Until then it hardcoded switches to a required state. It
         * returns an error code after running.
         * @return error_code : int
         * An int error code that returns the successfulness of the run of this
         * function.
         */
        int wait_command();

        /**
         * @brief
         * Function that initializes a robos_role object.
         * @detail
         * State function that is run when robOS is in the initrole state. It
         * checks the role variable and creates the required role object based
         * on that, changing the pointer of current_role to that one.
         * @return error_code : int
         * An int error code that returns the successfulness of the run of this
         * function.
         */
        int init_role();

        /**
         * @brief
         * Function that runs the process function of the currently active role.
         * @detail
         * State function that is run when the current state is the runrole
         * state. It passes a reference to the ringbuffer which can contain
         * packets that are required by the role.
         * @parameter ringbuffer : ringbuffer_c<std::array<uint8_t, 256>, 32> &
         * ringbuffer that can contain deconstructed frames for the role.
         * @return error_code : int
         * An int error code that returns the successfulness of the run of this
         * function.
         */
        int run_role(ringbuffer_c<std::array<uint8_t, 256>, 32> &ringbuffer);

        /**
         * @brief
         * Function that requests and stores identity packets of connected
         * modules from the can bus.
         * @detail
         * This function sends out an identity packet request on the can bus
         * which responds with identity frames from each module. These identity
         * enums are then returned and stored in the module list.
         */
        int update_modules();

        /**
         * @brief
         * Function that shuts down robOS.
         * @detail
         * Future function that calls the cleanup function from current_role,
         * deconstructs any existing objects and sets the shutdown bool on true,
         * thereby ending the process function and with it, robOS.
         */
        int shutdown_robos();
    };
} // namespace r2d2::robos