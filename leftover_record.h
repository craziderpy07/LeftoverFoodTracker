#ifndef LEFTOVER_RECORD_H
#define LEFTOVER_RECORD_H

// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include <string>

class LeftoverRecord {
 public:
  LeftoverRecord();

  const std::string& GetDate() const;
  const std::string& GetMeal() const;
  const std::string& GetFoodName() const;
  double GetQuantity() const;
  const std::string& GetLeftoverReason() const;
  const std::string& GetDisposalMechanism() const;
  double GetCost() const;

  void SetDate(const std::string& date);
  void SetMeal(const std::string& meal);
  void SetFoodName(const std::string& food_name);
  void SetQuantity(double qty_in_oz);
  void SetLeftoverReason(const std::string& leftover_reason);
  void SetDisposalMechanism(const std::string& disposal_mechanism);
  void SetCost(double cost);

 private:
  std::string date_;
  std::string meal_;
  std::string food_name_;
  double qty_in_oz_;
  std::string leftover_reason_;
  std::string disposal_mechanism_;
  double cost_;
};

#endif
