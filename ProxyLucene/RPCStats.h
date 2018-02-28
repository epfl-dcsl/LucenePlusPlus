/*
 *  Copyright (c) 2017, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

namespace RPCService {

/**
 * Just some dummy class containing request count. Since we keep
 * one instance of this in each class, there is no need of
 * synchronization
 */
class RPCStats {
 public:
  virtual ~RPCStats() {
  }

  virtual void recordRequest() {
    ++reqCount_;
  }

  virtual uint64_t getRequestCount() {
    return reqCount_;
  }

 private:
  uint64_t reqCount_{0};
};

}
