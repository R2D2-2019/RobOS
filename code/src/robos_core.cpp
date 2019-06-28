#include <robos_core.hpp>

namespace r2d2::robos_core{
	robos_core_c::robos_core_c(base_comm_c &comm) : base_module_c(comm){
		//connect with server here? or in an init function?
	};
	
	void robos_core_c::process(){};
	
	int robos_core_c::run(){return 0;};
	
	int robos_core_c::wait_command(){return 0;};
	int robos_core_c::init_role(){return 0;};
	int robos_core_c::run_role(){return 0;};
	int robos_core_c::shutdown_robos(){return 0;};
	
	
		
	
}