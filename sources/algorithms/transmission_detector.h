#pragma once

#include <algorithms/noise_learner.h>
#include <algorithms/torn_transmission_detector.h>
#include <config.h>
#include <radio/help_structures.h>

#include <chrono>
#include <map>
#include <shared_mutex>
#include <vector>

class TransmissionDetector {
 public:
  TransmissionDetector(const Config& config);
  ~TransmissionDetector();

  std::vector<std::pair<FrequencyRange, bool>> getTransmissions(const std::chrono::milliseconds& time, const std::vector<Signal>& signals);

 private:
  void updateTransmissionLastSignalTime(const std::chrono::milliseconds& time, const std::vector<Signal>& signals, const uint32_t step);
  std::vector<std::pair<FrequencyRange, bool>> getTransmissionWithActiveFlag(const std::chrono::milliseconds& time, const FrequencyRange& start, const FrequencyRange& stop) const;
  FrequencyRange getTransmission(const Frequency& frequency, const uint32_t step) const;

  mutable std::shared_mutex m_mutex;
  const Config& m_config;
  NoiseLearner m_noiseLearner;
  TornTransmissionDetector m_tornTransmissionDetector;
  std::map<FrequencyRange, std::chrono::milliseconds> m_transmissionLastSignalTime;
};
