/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <folly/logging/AsyncLogWriter.h>
#include <vector>

#include "IWritableFile.h"

namespace hf3fs::logging {
/**
 * An implementation of `folly::AsyncLogWriter` that writes log messages into a
 * file.
 *
 * See `folly::AsyncLogWriter` for details on asynchronous IO.
 */
class AsyncFileWriter : public folly::AsyncLogWriter {
 public:
  /**
   * Construct an AsyncFileWriter that writes to the specified File object.
   */
  explicit AsyncFileWriter(std::shared_ptr<IWritableFile> file);

  ~AsyncFileWriter();

  /**
   * Returns true if the output steam is a tty.
   */
  bool ttyOutput() const override;

 private:
  void writeToFile(const std::vector<std::string> &ioQueue, size_t numDiscarded);

  void performIO(const std::vector<std::string> &ioQueue, size_t numDiscarded) override;

  std::string getNumDiscardedMsg(size_t numDiscarded);

  std::shared_ptr<IWritableFile> file_;
};
}  // namespace hf3fs::logging
