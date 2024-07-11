#include "leftover_tracker_backend.h"

#include <filesystem>

#include "leftover_record.h"
#include "leftover_report.h"
#include "server_utils/rapidjson/document.h"      // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

// Util function to convert a LeftoverRecord class object into a serialized
// JSON object.
void SerializeLeftoverRecordToJSON(
    const LeftoverRecord &record,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->String("date_");  // DO NOT MODIFY

  std::string date = record.GetDate();

  writer->String(date.c_str());

  writer->String("meal_");  // DO NOT MODIFY

  std::string meal = record.GetMeal();

  writer->String(meal.c_str());

  writer->String("food_name_");  // DO NOT MODIFY

  std::string food_name = record.GetFoodName();

  writer->String(food_name.c_str());

  writer->String("qty_in_oz_");  // DO NOT MODIFY

  double quantity = record.GetQuantity();

  writer->Double(quantity);

  writer->String("leftover_reason_");  // DO NOT MODIFY

  std::string leftover_reason = record.GetLeftoverReason();

  writer->String(leftover_reason.c_str());

  writer->String("disposal_mechanism_");  // DO NOT MODIFY

  std::string disposal_mechanism = record.GetDisposalMechanism();

  writer->String(disposal_mechanism.c_str());

  writer->String("cost_");  // DO NOT MODIFY

  double cost = record.GetCost();

  writer->Double(cost);

  writer->EndObject();
}

// Util function to convert a serialized JSON object in to a LeftoverRecord
// class object.
LeftoverRecord DeserializeLeftoverRecordFromJSON(
    const rapidjson::Value &json_obj) {
  LeftoverRecord record;
  std::string date = json_obj["date_"].GetString();
  record.SetDate(date);
  std::string meal = json_obj["meal_"].GetString();
  record.SetMeal(meal);
  std::string food_name = json_obj["food_name_"].GetString();
  record.SetFoodName(food_name);
  double quantity = json_obj["qty_in_oz_"].GetDouble();
  record.SetQuantity(quantity);
  std::string leftover_reason = json_obj["leftover_reason_"].GetString();
  record.SetLeftoverReason(leftover_reason);
  std::string disposal_mechanism = json_obj["disposal_mechanism_"].GetString();
  record.SetDisposalMechanism(disposal_mechanism);
  double cost = json_obj["cost_"].GetDouble();
  record.SetCost(cost);

  return record;
}

crow::json::wvalue LeftoverRecordToCrowJSON(const LeftoverRecord &record) {
  crow::json::wvalue record_json({});

  std::string date = record.GetDate();
  record_json["date"] = date;

  std::string meal = record.GetMeal();
  record_json["meal"] = meal;

  std::string food_name = record.GetFoodName();
  record_json["food_name"] = food_name;

  double quantity = record.GetQuantity();
  record_json["qty_in_oz"] = quantity;

  std::string leftover_reason = record.GetLeftoverReason();
  record_json["leftover_reason"] = leftover_reason;

  std::string disposal_mechanism = record.GetDisposalMechanism();
  record_json["disposal_mechanism"] = disposal_mechanism;

  double cost = record.GetCost();
  record_json["cost"] = cost;

  return record_json;
}

// Util function to convert a LeftoverReport object into a serialized
// JSON object.
crow::json::wvalue LeftoverReportToCrowJSON(const LeftoverReport &report) {
  crow::json::wvalue report_json({});

  std::vector<std::string> most_common_disposal_mechanisms =
      report.MostCommonDisposalMechanisms();
  report_json["most_common_disposal_mechanism_"] =
      most_common_disposal_mechanisms;

  std::vector<std::string> most_common_leftovers = report.MostCommonLeftovers();
  report_json["most_common_leftover_"] = most_common_leftovers;

  std::vector<std::string> most_common_leftover_reasons =
      report.MostCommonReasons();
  report_json["most_common_leftover_reason_"] = most_common_leftover_reasons;

  std::vector<std::string> most_costly_leftover_producing_meals =
      report.MostCostlyMeals();
  report_json["most_leftover_producing_meal_"] =
      most_costly_leftover_producing_meals;

  std::vector<std::string> suggested_strategies_to_reduce_leftover =
      report.SuggestedStrategies();
  report_json["suggested_strategies_to_reduce_leftover_"] =
      suggested_strategies_to_reduce_leftover;

  double total_cost_of_leftover = report.TotalCostOfLeftovers();
  report_json["total_cost_of_leftover_"] = total_cost_of_leftover;

  return report_json;
}

LeftoverRecord QueryStringToLeftoverRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record{};

  record.SetDate(query_string.get("date"));

  record.SetMeal(query_string.get("meal"));

  record.SetFoodName(query_string.get("food_name"));

  record.SetQuantity(std::stod(query_string.get("qty_in_oz")));

  record.SetLeftoverReason(query_string.get("leftover_reason"));

  record.SetDisposalMechanism(query_string.get("disposal_mechanism"));

  record.SetCost(std::stod(query_string.get("cost")));

  return record;
}

bool LeftoverTrackerBackend::LoadRecordsFromJSONFile() {
  std::ifstream records_file{leftover_records_filepath_};
  if (!records_file.is_open()) {
    std::filesystem::remove(leftover_records_filepath_);
    return false;
  }

  std::stringstream buffer;
  buffer << records_file.rdbuf();

  std::string s = buffer.str();
  rapidjson::Document doc;

  if (s.empty()) {
    std::filesystem::remove(leftover_records_filepath_);
    return false;
  }

  std::string validJson(s);

  bool doc_parse_error = doc.Parse(validJson.c_str()).HasParseError();
  if (doc_parse_error || !doc.IsArray()) {
    std::filesystem::remove(leftover_records_filepath_);
    return false;
  }

  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End();
       ++itr) {
    LeftoverRecord record = DeserializeLeftoverRecordFromJSON(*itr);

    leftover_tracker_.AddRecord(record);
  }

  records_file.close();
  return true;
}

bool LeftoverTrackerBackend::WriteRecordsToJSONFile() const {
  std::ofstream records_file{leftover_records_filepath_};
  // Get the records from leftover_tracker_, convert to JSON and
  // save to file.
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartArray();

  std::vector<LeftoverRecord> records = leftover_tracker_.GetAllRecords();

  for (LeftoverRecord record : records) {
    SerializeLeftoverRecordToJSON(record, &writer);
  }
  writer.EndArray();

  records_file << ss.GetString();

  records_file.flush();
  records_file.close();
  return true;
}

crow::json::wvalue LeftoverTrackerBackend::AddRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool add_result = leftover_tracker_.AddRecord(record);

  status["success"] = add_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::DeleteRecord(
    const crow::query_string &query_string) {
  LeftoverRecord record = QueryStringToLeftoverRecord(query_string);
  crow::json::wvalue status;

  bool delete_result = leftover_tracker_.DeleteRecord(record);

  status["success"] = delete_result;

  return status;
}

crow::json::wvalue LeftoverTrackerBackend::GetRecords() const {
  std::vector<LeftoverRecord> records = leftover_tracker_.GetAllRecords();

  crow::json::wvalue records_json({});
  records_json["num_records"] = records.size();

  std::vector<crow::json::wvalue> record_json_vector;
  for (const LeftoverRecord &record : records) {
    record_json_vector.push_back(LeftoverRecordToCrowJSON(record));
  }
  records_json["record_array"] = std::move(record_json_vector);
  return records_json;
}

crow::json::wvalue LeftoverTrackerBackend::GetLeftoverReport() const {
  LeftoverReport generated_report = leftover_tracker_.GenerateReport();

  return LeftoverReportToCrowJSON(generated_report);
}