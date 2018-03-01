#include <LuceneHeaders.h>
#include <ParallelMultiSearcher.h>

using namespace Lucene;

namespace RPCService {
class RPCSearcher {
public:
	// Must be called before using the object.
	static void Init(std::vector<String> indices);
	static RPCSearcher* Instance();
	// TODO: get a collector.
	void Search(QueryPtr query);
	void Search(String query);
private:
	RPCSearcher() {};
	RPCSearcher(RPCSearcher const&) {};
	RPCSearcher& operator=(RPCSearcher const&){};

	static RPCSearcher* s_instance;
	static SearcherPtr searcher;
	static QueryParserPtr parser;
};

} // Namespace RCPSearch

