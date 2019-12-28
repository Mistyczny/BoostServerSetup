#include "Server.h"

int main()
{
	try {
		std::cout << std::this_thread::get_id() << std::endl;
		Server server;
		server.start();
		server.run();
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}