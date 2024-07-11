// Please fill in below.
// Teresa To
// CPSC 121L-13
// 18 April 2024
// tto46@csu.fullerton.edu
// craziderpy07

#include "leftover_record.h"

LeftoverRecord::LeftoverRecord()
    : date_(""),
      meal_(""),
      food_name_(""),
      qty_in_oz_(0.0),
      leftover_reason_(""),
      disposal_mechanism_(""),
      cost_(0.0) {}

const std::string& LeftoverRecord::GetDate() const { return date_; }
const std::string& LeftoverRecord::GetMeal() const { return meal_; }
const std::string& LeftoverRecord::GetFoodName() const { return food_name_; }
double LeftoverRecord::GetQuantity() const { return qty_in_oz_; }
const std::string& LeftoverRecord::GetLeftoverReason() const {
  return leftover_reason_;
}
const std::string& LeftoverRecord::GetDisposalMechanism() const {
  return disposal_mechanism_;
}
double LeftoverRecord::GetCost() const { return cost_; }
void LeftoverRecord::SetDate(const std::string& date) { date_ = date; }
void LeftoverRecord::SetMeal(const std::string& meal) { meal_ = meal; }
void LeftoverRecord::SetFoodName(const std::string& food_name) {
  food_name_ = food_name;
}
void LeftoverRecord::SetQuantity(double qty_in_oz) { qty_in_oz_ = qty_in_oz; }
void LeftoverRecord::SetLeftoverReason(const std::string& leftover_reason) {
  leftover_reason_ = leftover_reason;
}
void LeftoverRecord::SetDisposalMechanism(
    const std::string& disposal_mechanism) {
  disposal_mechanism_ = disposal_mechanism;
}
void LeftoverRecord::SetCost(double cost) { cost_ = cost; }
