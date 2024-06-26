/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "cyber/common/macros.h"
#include "modules/perception/common/lib/interface/base_init_options.h"
#include "modules/perception/common/lib/registerer/registerer.h"
#include "modules/perception/multi_sensor_fusion/base/base_forward_declaration.h"
#include "modules/perception/multi_sensor_fusion/base/scene.h"
#include "modules/perception/multi_sensor_fusion/base/sensor_frame.h"

namespace apollo {
namespace perception {
namespace fusion {

struct AssociationInitOptions : public BaseInitOptions {};

struct AssociationOptions {};

typedef std::pair<size_t, size_t> TrackMeasurmentPair;

struct AssociationResult {
  std::vector<TrackMeasurmentPair> assignments;
  std::vector<size_t> unassigned_tracks;
  std::vector<size_t> unassigned_measurements;
  std::vector<double> track2measurements_dist;
  std::vector<double> measurement2track_dist;
};

class BaseDataAssociation {
 public:
  BaseDataAssociation() = default;
  virtual ~BaseDataAssociation() = default;

  /**
   * @brief Init base data association config
   *
   * @param options init options
   * @return true
   * @return false
   */
  virtual bool Init(const AssociationInitOptions& options) = 0;

  /**
   * @brief associate sensor measurements with global scene
   *
   * @param options
   * @param sensor_measurements sensor measurements
   * @param scene container to store trace information
   * @param association_result association result
   * @return true
   * @return false
   */
  virtual bool Associate(const AssociationOptions& options,
                         SensorFramePtr sensor_measurements, ScenePtr scene,
                         AssociationResult* association_result) = 0;

  /**
   * @brief The name of BaseDataAssociation
   *
   * @return std::string
   */
  virtual std::string Name() const = 0;

  DISALLOW_COPY_AND_ASSIGN(BaseDataAssociation);
};

PERCEPTION_REGISTER_REGISTERER(BaseDataAssociation);
#define PERCEPTION_REGISTER_ASSOCIATION(name) \
  PERCEPTION_REGISTER_CLASS(BaseDataAssociation, name)

}  // namespace fusion
}  // namespace perception
}  // namespace apollo
