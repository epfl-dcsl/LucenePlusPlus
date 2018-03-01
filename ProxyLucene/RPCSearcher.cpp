#include <iostream>
#include "RPCSearcher.h"

using namespace RPCSearch;
using namespace Lucene;

RPCSearcher* RPCSearcher::s_instance = NULL;
SearcherPtr RPCSearcher::searcher = NULL;

void RPCSearcher::Init(std::vector<String> indices) {
	Collection<SearchablePtr> searchers = Collection<SearchablePtr>::newInstance();
	for (int i = 0; i < indices.size(); i++) {
		RAMDirectoryPtr ram = newLucene<RAMDirectory>(FSDirectory::open(indices[i]), true);
		IndexReaderPtr reader = IndexReader::open(ram, true);
		SearcherPtr idxsearcher = newLucene<IndexSearcher>(reader);
		searchers.add(idxsearcher);
	}
	searcher = newLucene<ParallelMultiSearcher>(searchers);
}

RPCSearcher* RPCSearcher::Instance() {
	if (!searcher) {
		std::cerr << "Call to RPCSearcher::Instance before the call to RPCSearcher::Init\n";
		exit(1);
	}
	if (!s_instance) {
		s_instance = new RPCSearcher;
	}
	return s_instance;
}

void RPCSearcher::Search(QueryPtr query) {

}

