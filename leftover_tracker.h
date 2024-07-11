#ifndef LEFTOVER_TRACKER_H
#define LEFTOVER_TRACKER_H

// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include <vector>

#include "leftover_record.h"
#include "leftover_report.h"

class LeftoverTracker {
 public:
  LeftoverTracker();

  bool AddRecord(const LeftoverRecord& record);
  bool DeleteRecord(const LeftoverRecord& record);
  std::vector<LeftoverRecord> GetAllRecords() const;
  LeftoverReport GenerateReport() const;

 private:
  std::vector<LeftoverRecord> records_;
};

#endif
