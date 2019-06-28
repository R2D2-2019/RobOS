#pragma once
#include <base_module.hpp>

namespace r2d2::robos_core{
	
	enum robos_state{
		wait,
		initrole,
		runrole,
		shutdown
	};

	class robos_core_c : public base_module_c{
	private:
		uint_fast16_t id;
		int mod_list [20];
		robos_state state;
	public:
		void process() override;
		robos_core_c(base_comm_c &comm) : base_module_c(comm){
			comm.configure(r2d2::frame_type::ALL);
		}
		int get_identity_packets();
		int run();
		int wait_command();
		int init_role();
		int run_role();
		int shutdown_robos();
		
		
	};
}