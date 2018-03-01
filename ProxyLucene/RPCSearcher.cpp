#include <iostream>
#include "RPCSearcher.h"

using namespace RPCService;
using namespace Lucene;

RPCSearcher* RPCSearcher::s_instance = NULL;
SearcherPtr RPCSearcher::searcher = NULL;
QueryParserPtr RPCSearcher::parser = NULL;

void RPCSearcher::Init(std::vector<String> indices) {
	Collection<SearchablePtr> searchers = Collection<SearchablePtr>::newInstance();
	for (int i = 0; i < indices.size(); i++) {
		RAMDirectoryPtr ram = newLucene<RAMDirectory>(FSDirectory::open(indices[i]), true);
		IndexReaderPtr reader = IndexReader::open(ram, true);
		SearcherPtr idxsearcher = newLucene<IndexSearcher>(reader);
		searchers.add(idxsearcher);
	}
	searcher = newLucene<ParallelMultiSearcher>(searchers);

	AnalyzerPtr analyzer = newLucene<StandardAnalyzer>(LuceneVersion::LUCENE_CURRENT);
	parser = newLucene<QueryParser>(LuceneVersion::LUCENE_CURRENT, L"contents", analyzer);
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
	std::wcout << L"Starting a search\n";
	searcher->search(query, FilterPtr(), 100);
	std::wcout << L"Ending a search\n";
}

void RPCSearcher::Search(String query) {
	QueryPtr q = parser->parse(query);
	Search(q);
}

