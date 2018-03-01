#include <iostream>
#include <proxygen/httpserver/HTTPServer.h>
#include "RPCHandler.h"

using namespace proxygen;

// Forward declaration for the initialization of the server.
HTTPServer* initServer(char *name);

int main(int argc, char* argv[]) {
	std::wcout << "Something is supposed to be implemented soonish\n";
	HTTPServer* server = initServer(argv[0]);
	// Start HTTPServer mainloop in a separate thread
	std::thread t([&] () {
		server->start();
	});
	t.join();
	return 0;
}