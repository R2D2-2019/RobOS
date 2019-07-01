#include <robos_core.hpp>

namespace r2d2::robos_core{
	robos_core_c::robos_core_c(base_comm_c &comm)
        : base_module_c(comm) {
        comm.configure(r2d2::modules::NONE, {r2d2::frame_type::ALL});
    }
	
	void robos_core_c::process(){
		bool end = false;
		int error_code;
		while(!end){


			switch(robos_core_c::state){
				case wait : error_code = robos_core_c::wait_command();
					break;
				case initrole : error_code = robos_core_c::init_role();
					break;
				case runrole : error_code = robos_core_c::run_role();
					break;
				case updatemodules : error_code = robos_core_c::update_modules();
					break;
				case shutdown : error_code = robos_core_c::shutdown_robos();
					end = true;
			}
			end = true;
		}
	};
	
	int robos_core_c::wait_command(){return 0;};
	int robos_core_c::init_role(){return 0;};
	int robos_core_c::run_role(){return 0;};
	int robos_core_c::shutdown_robos(){return 0;};
	
	int robos_core_c::update_modules(){
		return 0;
	};
		
	
}