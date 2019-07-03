#pragma once

namespace r2d2::robos {

    enum class robos_state { WAIT, INITROLE, RUNROLE, UPDATEMODULES, SHUTDOWN };

    enum class robos_roles { MANUAL_CONTROL, MOVING_PLATFORM, EXAMPLE_ROLE };

}