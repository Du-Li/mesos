/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TYPE_UTILS_HPP__
#define __TYPE_UTILS_HPP__

#include <boost/functional/hash.hpp>

#include <google/protobuf/descriptor.h>

#include <mesos/mesos.hpp>
#include <mesos/resources.hpp>

#include <stout/uuid.hpp>

#include "common/attributes.hpp"

#include "messages/messages.hpp"

// This file includes definitions for operators on protobuf classes
// that don't have these operators generated by the protobuf compiler.

namespace mesos {

inline std::ostream& operator << (
    std::ostream& stream,
    const FrameworkID& frameworkId)
{
  return stream << frameworkId.value();
}


inline std::ostream& operator << (std::ostream& stream, const OfferID& offerId)
{
  return stream << offerId.value();
}


inline std::ostream& operator << (std::ostream& stream, const SlaveID& slaveId)
{
  return stream << slaveId.value();
}


inline std::ostream& operator << (std::ostream& stream, const TaskID& taskId)
{
  return stream << taskId.value();
}


inline std::ostream& operator << (
    std::ostream& stream,
    const ExecutorID& executorId)
{
  return stream << executorId.value();
}


inline std::ostream& operator << (std::ostream& stream, const TaskState& state)
{
  return stream << TaskState_descriptor()->FindValueByNumber(state)->name();
}


inline std::ostream& operator << (std::ostream& stream, const TaskInfo& task)
{
  return stream << task.DebugString();
}


inline std::ostream& operator << (std::ostream& stream, const SlaveInfo& slave)
{
  return stream << slave.DebugString();
}


inline std::ostream& operator << (
    std::ostream& stream,
    const ExecutorInfo& executor)
{
  return stream << executor.DebugString();
}


inline bool operator == (const FrameworkID& left, const FrameworkID& right)
{
  return left.value() == right.value();
}


inline bool operator == (const FrameworkInfo& left, const FrameworkInfo& right)
{
  return (left.name() == right.name()) && (left.user() == right.user());
}


inline bool operator == (const Credential& left, const Credential& right)
{
  return left.principal() == right.principal() &&
         left.has_secret() == right.has_secret() &&
         (!left.has_secret() || (left.secret() == right.secret()));
}


inline bool operator == (const OfferID& left, const OfferID& right)
{
  return left.value() == right.value();
}


inline bool operator == (const SlaveID& left, const SlaveID& right)
{
  return left.value() == right.value();
}


inline bool operator == (const TaskID& left, const TaskID& right)
{
  return left.value() == right.value();
}


inline bool operator == (const ExecutorID& left, const ExecutorID& right)
{
  return left.value() == right.value();
}


inline bool operator == (const FrameworkID& left, const std::string& right)
{
  return left.value() == right;
}


inline bool operator == (const OfferID& left, const std::string& right)
{
  return left.value() == right;
}


inline bool operator == (const SlaveID& left, const std::string& right)
{
  return left.value() == right;
}


inline bool operator == (const TaskID& left, const std::string& right)
{
  return left.value() == right;
}


inline bool operator == (const ExecutorID& left, const std::string& right)
{
  return left.value() == right;
}


inline bool operator < (const FrameworkID& left, const FrameworkID& right)
{
  return left.value() < right.value();
}


inline bool operator < (const OfferID& left, const OfferID& right)
{
  return left.value() < right.value();
}


inline bool operator < (const SlaveID& left, const SlaveID& right)
{
  return left.value() < right.value();
}


inline bool operator < (const TaskID& left, const TaskID& right)
{
  return left.value() < right.value();
}


inline bool operator < (const ExecutorID& left, const ExecutorID& right)
{
  return left.value() < right.value();
}


inline bool operator == (const Environment& left, const Environment& right)
{
  if (left.variables().size() != right.variables().size()) {
    return false;
  }

  for (int i = 0; i < left.variables().size(); i++) {
    const std::string& name = left.variables().Get(i).name();
    const std::string& value = left.variables().Get(i).value();
    bool found = false;
    for (int j = 0; j < right.variables().size(); j++) {
      if (name == right.variables().Get(j).name() &&
          value == right.variables().Get(j).value()) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }

  return true;
}


inline bool operator == (
    const CommandInfo::URI& left,
    const CommandInfo::URI& right)
{
  return left.has_executable() == right.has_executable() &&
    (!left.has_executable() || (left.executable() == right.executable())) &&
    left.value() == right.value();
}


inline bool operator == (const CommandInfo& left, const CommandInfo& right)
{
  if (left.uris().size() != right.uris().size()) {
    return false;
  }

  for (int i=0; i<left.uris().size(); i++) {
    bool found = false;
    for (int j=0; j<right.uris().size(); j++) {
      if (left.uris().Get(i) == right.uris().Get(j)) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }

  return left.has_environment() == right.has_environment() &&
    (!left.has_environment() || (left.environment() == right.environment())) &&
    left.value() == right.value();
}


inline bool operator == (const ExecutorInfo& left, const ExecutorInfo& right)
{
  return left.executor_id() == right.executor_id() &&
    left.has_framework_id() == right.has_framework_id() &&
    (!left.has_framework_id() ||
    (left.framework_id() == right.framework_id())) &&
    left.command() == right.command() &&
    Resources(left.resources()) == Resources(right.resources()) &&
    left.has_name() == right.has_name() &&
    (!left.has_name() || (left.name() == right.name())) &&
    left.has_source() == right.has_source() &&
    (!left.has_source() || (left.source() == right.source())) &&
    left.has_data() == right.has_data() &&
    (!left.has_data() || (left.data() == right.data()));
}


inline bool operator == (const SlaveInfo& left, const SlaveInfo& right)
{
  return left.hostname() == right.hostname() &&
    Resources(left.resources()) == Resources(right.resources()) &&
    internal::Attributes(left.attributes()) ==
    internal::Attributes(right.attributes()) &&
    left.has_id() == right.has_id() &&
    (!left.has_id() || (left.id() == right.id())) &&
    left.has_checkpoint() == right.has_checkpoint() &&
    (!left.has_checkpoint() || (left.checkpoint() == right.checkpoint()));
}


inline std::size_t hash_value(const FrameworkID& frameworkId)
{
  size_t seed = 0;
  boost::hash_combine(seed, frameworkId.value());
  return seed;
}


inline std::size_t hash_value(const OfferID& offerId)
{
  size_t seed = 0;
  boost::hash_combine(seed, offerId.value());
  return seed;
}


inline std::size_t hash_value(const SlaveID& slaveId)
{
  size_t seed = 0;
  boost::hash_combine(seed, slaveId.value());
  return seed;
}


inline std::size_t hash_value(const TaskID& taskId)
{
  size_t seed = 0;
  boost::hash_combine(seed, taskId.value());
  return seed;
}


inline std::size_t hash_value(const ExecutorID& executorId)
{
  size_t seed = 0;
  boost::hash_combine(seed, executorId.value());
  return seed;
}


namespace internal {

inline bool operator == (const Task& left, const Task& right)
{
  return left.name() == right.name() &&
    left.task_id() == right.task_id() &&
    left.framework_id() == right.framework_id() &&
    left.slave_id() == right.slave_id() &&
    left.state() == right.state() &&
    Resources(left.resources()) == Resources(right.resources()) &&
    left.has_executor_id() == right.has_executor_id() &&
    (!left.has_executor_id() || (left.executor_id() == right.executor_id()));
}


inline std::ostream& operator << (
    std::ostream& stream,
    const StatusUpdate& update)
{
  return stream
    << update.status().state()
    << " (UUID: " << UUID::fromBytes(update.uuid())
    << ") for task " << update.status().task_id()
    << " of framework " << update.framework_id();
}


inline std::ostream& operator << (
    std::ostream& stream,
    const StatusUpdateRecord::Type& type)
{
  return stream
    << StatusUpdateRecord::Type_descriptor()->FindValueByNumber(type)->name();
}

}} // namespace mesos { namespace internal {

#endif // __TYPE_UTILS_HPP__
