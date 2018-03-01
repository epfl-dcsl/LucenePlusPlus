#include <iostream>
#include <proxygen/httpserver/HTTPServer.h>
#include "RPCHandler.h"
#include "RPCSearcher.h"

using namespace Lucene;
using namespace proxygen;

// Forward declaration for the initialization of the server.
HTTPServer* initServer(char *name);

int main(int argc, char* argv[]) {
	std::cout << "Something is supposed to be implemented soonish\n";
	HTTPServer* server = initServer(argv[0]);
	std::vector<String> indices;
	for (int i = 1; i < argc; i ++) {
		indices.push_back(StringUtils::toUnicode(argv[i]));
	}

	RPCService::RPCSearcher::Init(indices);

	// Start HTTPServer mainloop in a separate thread
	std::thread t([&] () {
		server->start();
	});
	t.join();
	return 0;
}