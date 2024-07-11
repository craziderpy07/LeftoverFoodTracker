// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include "leftover_tracker.h"

#include <algorithm>
#include <vector>

LeftoverTracker::LeftoverTracker() {}

bool LeftoverTracker::AddRecord(const LeftoverRecord& record) {
  for (const LeftoverRecord& r : records_) {
    if (r.GetDate() == record.GetDate() && r.GetMeal() == record.GetMeal() &&
        r.GetFoodName() == record.GetFoodName() &&
        r.GetQuantity() == record.GetQuantity() &&
        r.GetLeftoverReason() == record.GetLeftoverReason() &&
        r.GetDisposalMechanism() == record.GetDisposalMechanism() &&
        r.GetCost() == record.GetCost()) {
      return false;
    }
  }

  records_.push_back(record);
  return true;
}

bool LeftoverTracker::DeleteRecord(const LeftoverRecord& record) {
  for (auto it = records_.begin(); it != records_.end(); ++it) {
    if ((*it).GetDate() == record.GetDate() &&
        (*it).GetMeal() == record.GetMeal() &&
        (*it).GetFoodName() == record.GetFoodName() &&
        (*it).GetQuantity() == record.GetQuantity() &&
        (*it).GetLeftoverReason() == record.GetLeftoverReason() &&
        (*it).GetDisposalMechanism() == record.GetDisposalMechanism() &&
        (*it).GetCost() == record.GetCost()) {
      records_.erase(it);
      return true;
    }
  }
  return false;
}

std::vector<LeftoverRecord> LeftoverTracker::GetAllRecords() const {
  return records_;
}

LeftoverReport LeftoverTracker::GenerateReport() const {
  return LeftoverReport(records_);
}
