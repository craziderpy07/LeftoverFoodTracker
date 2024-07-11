// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include "leftover_report.h"

#include "leftover_record.h"
#include "leftover_tracker_backend.h"

LeftoverReport::LeftoverReport() {}
LeftoverReport::LeftoverReport(const std::vector<LeftoverRecord>& records)
    : records_(records) {}

std::vector<std::string> LeftoverReport::MostCommonLeftovers() const {
  std::vector<std::string> mostCommonLeftovers;

  std::unordered_map<std::string, int> leftoverCounts;
  for (const LeftoverRecord& record : records_) {
    leftoverCounts[record.GetFoodName()]++;
  }

  int maxCount = 0;
  for (const auto& pair : leftoverCounts) {
    maxCount = std::max(maxCount, pair.second);
  }

  for (const auto& pair : leftoverCounts) {
    if (pair.second == maxCount) {
      mostCommonLeftovers.push_back(pair.first);
    }
  }

  return mostCommonLeftovers;
}

std::vector<std::string> LeftoverReport::MostCostlyMeals() const {
  std::unordered_map<std::string, int> mealCount;

  for (const LeftoverRecord& meal : records_) {
    mealCount[meal.GetMeal()]++;
  }

  std::vector<std::string> mostCostlyMeals;
  int maxCount = 0;

  for (const auto& pair : mealCount) {
    if (pair.second > maxCount) {
      maxCount = pair.second;
    }
  }

  for (const auto& pair : mealCount) {
    if (pair.second == maxCount) {
      mostCostlyMeals.push_back(pair.first);
    }
  }

  return mostCostlyMeals;
}

double LeftoverReport::TotalCostOfLeftovers() const {
  double totalCost = 0.0;
  for (const LeftoverRecord& record : records_) {
    totalCost += record.GetCost();
  }
  return totalCost;
}

std::vector<std::string> LeftoverReport::MostCommonReasons() const {
  std::vector<std::string> mostCommonReasons;

  std::unordered_map<std::string, int> reasonCounts;
  for (const LeftoverRecord& record : records_) {
    reasonCounts[record.GetLeftoverReason()]++;
  }
  int maxCount = 0;
  for (const auto& pair : reasonCounts) {
    maxCount = std::max(maxCount, pair.second);
  }

  for (const auto& pair : reasonCounts) {
    if (pair.second == maxCount) {
      mostCommonReasons.push_back(pair.first);
    }
  }
  return mostCommonReasons;
}

std::vector<std::string> LeftoverReport::MostCommonDisposalMechanisms() const {
  std::vector<std::string> mostCommonDisposalMechanisms;

  std::unordered_map<std::string, int> disposalCounts;
  for (const LeftoverRecord& record : records_) {
    disposalCounts[record.GetDisposalMechanism()]++;
  }

  int maxCount = 0;
  for (const auto& pair : disposalCounts) {
    maxCount = std::max(maxCount, pair.second);
  }

  for (const auto& pair : disposalCounts) {
    if (pair.second == maxCount) {
      mostCommonDisposalMechanisms.push_back(pair.first);
    }
  }

  return mostCommonDisposalMechanisms;
}

std::vector<std::string> LeftoverReport::SuggestedStrategies() const {
  std::vector<std::string> suggestedStrategies;
  bool expired = false;
  bool lessFoodAdded = false;
  for (const auto& reason : LeftoverReport::MostCommonReasons()) {
    if (reason == "Expired") {
      expired = true;
      suggestedStrategies.push_back("Donate before expiration");
    }
    if (reason == "Too much left overs") {
      suggestedStrategies.push_back("Cook small servings");
    }
    if ((reason == "Too much left overs" || reason == "Tastes bad") &&
        lessFoodAdded == false) {
      lessFoodAdded = true;
      suggestedStrategies.push_back("Buy less food");
    }
  }
  if (expired == false && lessFoodAdded == true) {
    suggestedStrategies.push_back("Recycle left overs");
  }
  return suggestedStrategies;
}
