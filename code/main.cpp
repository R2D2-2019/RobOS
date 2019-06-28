#include <robos_core.hpp>
#include <comm.hpp>

int main( void ){	
	r2d2::comm_c comm;
	auto robos_core_c = r2d2::robos_core::robos_core_c(comm);
	
	robos_core_c.process();
}