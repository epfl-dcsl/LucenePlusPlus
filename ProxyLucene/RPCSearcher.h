#include <LuceneHeaders.h>
#include <ParallelMultiSearcher.h>

using namespace Lucene;

namespace RPCSearch {
class RPCSearcher {
public:
	// Must be called before using the object.
	static void Init(std::vector<String> indices);
	static RPCSearcher* Instance();
	// TODO: get a collector.
	void Search(QueryPtr query);
	
private:
	RPCSearcher() {};
	RPCSearcher(RPCSearcher const&) {};
	RPCSearcher& operator=(RPCSearcher const&){};

	static RPCSearcher* s_instance;
	static SearcherPtr searcher;
};

} // Namespace RCPSearch

