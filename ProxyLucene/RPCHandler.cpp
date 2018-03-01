/*
	*  Copyright (c) 2017, Facebook, Inc.
	*  All rights reserved.
	*
	*  This source code is licensed under the BSD-style license found in the
	*  LICENSE file in the root directory of this source tree. An additional grant
	*  of patent rights can be found in the PATENTS file in the same directory.
	*
	*/
#include <iostream>
#include "RPCHandler.h"

#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

#include "RPCStats.h"
#include "RPCSearcher.h"

using namespace proxygen;

namespace RPCService {

RPCHandler::RPCHandler(RPCStats* stats): stats_(stats) {
}

void RPCHandler::onRequest(std::unique_ptr<HTTPMessage> /*headers*/) noexcept {
	stats_->recordRequest();
}

void RPCHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
	if (body_) {
			body_->prependChain(std::move(body));
	} else {
			body_ = std::move(body);
	}
}

void RPCHandler::onEOM() noexcept {
	// Get the terms we are looking for. 
	if (body_ != NULL) {
		std::cout << "The length "<< body_->length() << std::endl;
		Lucene::String bd = Lucene::StringUtils::toUnicode(reinterpret_cast<const char*>(body_->data()));
		std::cout << "The body has been parsed\n ";
		RPCSearcher::Instance()->Search(bd);
	}

	ResponseBuilder(downstream_)
	  .status(200, "OK")
	  .header("Request-Number",
	          folly::to<std::string>(stats_->getRequestCount()))
	  .body(std::move(body_))
	  .sendWithEOM();
}

void RPCHandler::onUpgrade(UpgradeProtocol /*protocol*/) noexcept {
	// handler doesn't support upgrades
}

void RPCHandler::requestComplete() noexcept {
	delete this;
}

void RPCHandler::onError(ProxygenError /*err*/) noexcept { delete this; }
}
