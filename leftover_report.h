#ifndef LEFTOVER_REPORT_H
#define LEFTOVER_REPORT_H

// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include <string>
#include <vector>

#include "leftover_record.h"

class LeftoverReport {
 public:
  LeftoverReport();
  LeftoverReport(const std::vector<LeftoverRecord>& records);

  std::vector<std::string> MostCommonLeftovers() const;
  std::vector<std::string> MostCostlyMeals() const;
  double TotalCostOfLeftovers() const;
  std::vector<std::string> MostCommonReasons() const;
  std::vector<std::string> MostCommonDisposalMechanisms() const;
  std::vector<std::string> SuggestedStrategies() const;

 private:
  std::vector<LeftoverRecord> records_;
};

#endif
