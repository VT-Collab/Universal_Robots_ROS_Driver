// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// Copyright 2019 FZI Forschungszentrum Informatik
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Tristan Schnell schnell@fzi.de
 * \date    2019-04-10
 *
 */
//----------------------------------------------------------------------

#ifndef UR_RTDE_DRIVER_RTDE_CLIENT_H_INCLUDED
#define UR_RTDE_DRIVER_RTDE_CLIENT_H_INCLUDED

#include "ur_rtde_driver/comm/pipeline.h"
#include "ur_rtde_driver/rtde/package_header.h"
#include "ur_rtde_driver/rtde/rtde_package.h"
#include "ur_rtde_driver/comm/stream.h"
#include "ur_rtde_driver/rtde/rtde_parser.h"
#include "ur_rtde_driver/comm/producer.h"
#include "ur_rtde_driver/rtde/data_package.h"
#include "ur_rtde_driver/rtde/request_protocol_version.h"
#include "ur_rtde_driver/rtde/control_package_setup_outputs.h"
#include "ur_rtde_driver/rtde/control_package_start.h"
#include "ur_rtde_driver/log.h"

static const int UR_RTDE_PORT = 30004;
static const std::string PIPELINE_NAME = "RTDE Data Pipeline";

namespace ur_driver
{
namespace rtde_interface
{
class RTDEClient
{
public:
  RTDEClient() = delete;
  RTDEClient(std::string ROBOT_IP, comm::INotifier& notifier);
  ~RTDEClient() = default;
  bool init();
  bool start();
  bool getDataPackage(std::unique_ptr<comm::URPackage<PackageHeader>>& data_package, std::chrono::milliseconds timeout);

  double getMaxFrequency() const
  {
    return max_frequency_;
  }

private:
  comm::URStream<PackageHeader> stream_;
  RTDEParser parser_;
  comm::URProducer<PackageHeader> prod_;
  comm::Pipeline<PackageHeader> pipeline_;

  double max_frequency_;

  constexpr static const double CB3_MAX_FREQUENCY = 125.0;
  constexpr static const double URE_MAX_FREQUENCY = 500.0;

  std::vector<std::string> readRecipe();
};

}  // namespace rtde_interface
}  // namespace ur_driver

#endif  // UR_RTDE_DRIVER_RTDE_CLIENT_H_INCLUDED
