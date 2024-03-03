#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <utility>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <assert.h>
#include "fmt/core.h"
#include "src/Dashboard.h"
#include "src/jsonObjects.h"


using namespace std;

namespace py = pybind11;

void testProject1(Project &project1) {
  auto taskList = project1.task_list;
  std::cout << "Type: " << std::endl;
  assert(taskList.size() == 1);
  for (auto &[classificationId, task]: taskList) {
    std::string key = "95887";
    assert(std::string(classificationId) == key);
    auto assignedUsers = task.assigned_users;
    assert(assignedUsers.size() == 6);
  }
}

int main() {
  std::locale::global(std::locale("en_US.UTF-8"));

  cout << "C++ version: " << __cplusplus << endl;

  //auto timeT = std::chrono::system_clock::to_time_t(tp);
  //
  //std::chrono::time_point now{std::chrono::system_clock::now()};
  //std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
  //auto yr = ymd.year();
  //auto yr2 = int(yr);
  //std::chrono::year_month_day ymd2 = std::chrono::
  const std::string in = "2022-01-01";
  std::stringstream ss(in);

  std::chrono::year_month_day ymd;


  auto organizationId = 4877;
  auto startDate = "2020-01-01";
  auto endDate = "2022-01-01";
  auto pendingCountBy = "creation";
  Dashboard dashboard{organizationId, startDate, endDate, pendingCountBy};
  auto thisUser = dashboard.getUserById(0);
  fmt::print("User: user_id: {}\n", thisUser.user_id);
  try {
    auto thirdUser = dashboard.getUserById(6);
  } catch (std::out_of_range &e) {
    std::cout << (std::string) e.what() << std::endl;
  }

  dashboard.populateConfigReportFromJson(configReportJson());
  auto &configReport = dashboard.configReport;
  auto goals = dashboard.configReport.goals;
  /**
   * Dashboard.handle_check() results
   */
  // user_id_list
  vector<int> userIds{1, 2, 3, 1};
  dashboard.appendToUserIdsList(userIds);
  auto userIdList = dashboard.user_id_list;
  // user_data
  auto userStr = userDataStr();
  dashboard.populateUserDataFromJsonStr(userStr);
  // team_data
  auto teamStr = teamDataStr();
  dashboard.populateTeamDataFromJsonStr(teamStr);

  dashboard.populateOrganizationContentTagsFromJsonStr(organizationContentTagsStr());
  /**
   * Project
   */
  auto b1 = project1str();
  dashboard.populateProjectFromJsonStr(b1);
  auto allTasks1 = dashboard.project.combineProjectTasks();
  auto acceptedTasks1 = dashboard.project.getAssignedTasks();
  dashboard.iterateAssignedTasks();
  std::cout << "**********************" << std::endl;
  testProject1(dashboard.projects[0]);
  auto b2 = task2str();
  dashboard.populateProjectFromJsonStr(b2);
  auto allTasks2 = dashboard.project.combineProjectTasks();
  auto acceptedTasks2 = dashboard.project.getAssignedTasks();
  auto b3 = project3str();
  dashboard.populateProjectFromJsonStr(b3);
  auto allTasks3 = dashboard.project.combineProjectTasks();
  auto acceptedTasks3 = dashboard.project.getAssignedTasks();
  auto b4 = project4str();
  dashboard.populateProjectFromJsonStr(b4);
  auto allTasks4 = dashboard.project.combineProjectTasks();
  auto acceptedTasks4 = dashboard.project.getAssignedTasks();
  return 0;
}

//PYBIND11_MAKE_OPAQUE(UserDataMap);
//PYBIND11_OBJECT()

/**
 @link https://pybind11.readthedocs.io/en/stable/basics.html#creating-bindings-for-a-simple-function

 This is a macro that created a function that will be called when an import statement is called from Python.
 The first argument is the module name (pm_tickets) that is used from python (import pm_tickets). The
 second argument (m) is a variable of type py::module_ that is the main interface to create bindings.
 py::module_::def() (here, m.def("add", ...)) generates binding code that exposes a function for Python:
 from pm_tickets import add
 When not specified, the function's arguments and return type are inferred
 */
PYBIND11_MODULE(pm_tickets, m) {
  std::locale::global(std::locale("en_US.UTF-8"));
  m.doc() = "pm_tickets";
  //m.def("add", &add, "A function to add two numbers");
  // Specify kwargs
  //m.def("add_with_kwargs", &add_with_kwargs, "A function to add two numbers using kwargs",
  //  py::arg("i"), py::arg("j"));
  /**
   Shorthand for specifying kwargs. Must specify using namespace to use literals
   The _a suffix forms a C++11 literal equivalent to pybind11 arg
   @link https://pybind11.readthedocs.io/en/stable/reference.html#_CPPv43arg
   */
  using namespace pybind11::literals;
  //m.def("add_with_kwargs2", &add_with_kwargs, "A function to add two numbers using kwargs and defaults",
  //  "i"_a = 5, "j"_a = 5);
  /**
   Variables can be exported to Python, but some may need to be cast into Python types
   @link https://pybind11.readthedocs.io/en/stable/basics.html#exporting-variables
   */
  //m.attr("the_answer") = 42;
  //py::object world = py::cast("World");
  //m.attr("what") = world;

  py::class_<AssignedUser>(m, "AssignedUser")
    .def(py::init())
    .def_readwrite("date_time", &AssignedUser::date_time)
    .def_readwrite("assigned_from", &AssignedUser::assigned_from)
    .def_readwrite("assigned_to", &AssignedUser::assigned_to)
    .def_readwrite("assigned_by", &AssignedUser::assigned_by);

  py::class_<Task>(m, "Task")
    .def(py::init())
    .def_readwrite("lightGBMPrediction_end", &Task::lightGBMPrediction_end)
    .def_readwrite("user_loe", &Task::user_loe)
    .def_readwrite("display_order", &Task::display_order)
    .def_readwrite("lightGBMPrediction_start", &Task::lightGBMPrediction_start)
    .def_readwrite("user_id", &Task::user_id)
    .def_readwrite("classifierPredication_loe", &Task::classifierPredication_loe)
    .def_readwrite("tasked_date", &Task::tasked_date)
    .def_readwrite("override_total", &Task::override_total)
    .def_readwrite("displayed", &Task::displayed)
    .def_readwrite("accepted", &Task::accepted)
    .def_readwrite("type", &Task::type)
    .def_readwrite("assigned_users", &Task::assigned_users)
    .def_readwrite("loe_per", &Task::loe_per)
    .def_readwrite("quantity", &Task::quantity)
    .def_readwrite("assignee_override_total", &Task::assignee_override_total)
    .def_readwrite("projected_assignee_total", &Task::projected_assignee_total)
    .def_readwrite("assignee_loe", &Task::assignee_loe)
    .def_readwrite("loe_per_unit", &Task::loe_per_unit);

  py::class_<Comment>(m, "Comment")
    .def(py::init())
    .def_readwrite("comment", &Comment::comment)
    .def_readwrite("date_time", &Comment::date_time)
    .def_readwrite("full_name", &Comment::full_name);

  py::class_<Project>(m, "Project")
    .def(py::init())
    .def_readwrite("_id", &Project::_id)
    .def_readwrite("organization_id", &Project::organization_id)
    .def_readwrite("creation_id", &Project::creation_id)
    .def_readwrite("creation", &Project::creation)
    .def_readwrite("updated", &Project::updated)
    .def_readwrite("last_name", &Project::last_name)
    .def_readwrite("task_dependencies", &Project::task_dependencies)
    .def_readwrite("completion_iso", &Project::completion_iso)
    .def_readwrite("creation_status", &Project::creation_status)
    .def_readwrite("classification_code", &Project::classification_code)
    .def_readwrite("avg_loe", &Project::avg_loe)
    .def_readwrite("task_list", &Project::task_list)
    .def_readwrite("ancillary_list", &Project::ancillary_list)
    .def_readwrite("taskDependenciesSub", &Project::taskDependenciesSub)
    .def_readwrite("user_language", &Project::user_language)
    .def_readwrite("first_name", &Project::first_name)
    .def_readwrite("estPoints", &Project::estPoints)
    .def_readwrite("is_shared", &Project::is_shared)
    .def_readwrite("creation_iso", &Project::creation_iso)
    .def_readwrite("sub_task_code", &Project::sub_task_code)
    .def_readwrite("completion", &Project::completion)
    .def_readwrite("user_email", &Project::user_email)
    .def_readwrite("validationId", &Project::validationId)
    .def_readwrite("los", &Project::los)
    .def_readwrite("relationship_id", &Project::relationship_id)
    .def_readwrite("from_userUpdates", &Project::from_userUpdates)
    .def_readwrite("classification_id", &Project::classification_id)
    .def_readwrite("status", &Project::status)
    .def_readwrite("comments", &Project::comments)
    .def_readwrite("created", &Project::created)
    .def_readwrite("user_id", &Project::user_id)
    .def_readwrite("accepted_lightGBMPredictions", &Project::accepted_lightGBMPredictions)
    .def_readwrite("projected_total_pendingCount", &Project::projected_total_pendingCount)
    .def_readwrite("assignee_total_pendingCount", &Project::assignee_total_pendingCount)
    .def_readwrite("projected_assignee_pendingCount", &Project::projected_assignee_pendingCount)
    .def("combineProjectTasks", &Project::combineProjectTasks)
    .def("getAssignedTasks", &Project::getAssignedTasks)
    .def("checkLoeEquity", &Project::checkLoeEquity);

  // UserData
  py::class_<UserData>(m, "UserData")
    .def(py::init())
    .def_readwrite("total_count", &UserData::total_count)
    .def_readwrite("eligible_count", &UserData::eligible_count)
    .def_readwrite("assignee_id", &UserData::assignee_id)
    .def_readwrite("pendingCount", &UserData::pendingCount)
    .def_readwrite("success_count", &UserData::success_count)
    .def_readwrite("user_id", &UserData::user_id)
    .def_readwrite("full_name", &UserData::full_name)
    .def_readwrite("success_rate", &UserData::success_rate)
    .def_readwrite("efficiency_rate", &UserData::efficiency_rate)
    .def_readwrite("user_id", &UserData::user_id);

  // TeamData
  py::class_<TeamData>(m, "TeamData")
    .def(py::init<>())
    .def_readwrite("team_total_count", &TeamData::team_total_count)
    .def_readwrite("team_eligible_count", &TeamData::team_eligible_count)
    .def_readwrite("team_pendingCount", &TeamData::team_pendingCount)
    .def_readwrite("team_average_pendingCount", &TeamData::team_average_pendingCount)
    .def_readwrite("team_target_pendingCount", &TeamData::team_target_pendingCount)
    .def_readwrite("team_target_count", &TeamData::team_target_count)
    .def_readwrite("team_average_count", &TeamData::team_average_count)
    .def_readwrite("team_target_percentage", &TeamData::team_target_percentage)
    .def_readwrite("team_average_percentage", &TeamData::team_average_percentage)
    .def_readwrite("team_success_count", &TeamData::team_success_count)
    .def_readwrite("team_success_rate", &TeamData::team_success_rate)
    .def_readwrite("team_efficiency_rate", &TeamData::team_efficiency_rate);

  py::class_<OrganizationContentClassification>(m, "OrganizationContentClassification")
    .def(py::init<>())
    .def_readwrite("STATUS", &OrganizationContentClassification::STATUS)
    .def_readwrite("ORDERING_TYPE", &OrganizationContentClassification::ORDERING_TYPE)
    .def_readwrite("NAME", &OrganizationContentClassification::NAME)
    .def_readwrite("RELATIONSHIP_CODES", &OrganizationContentClassification::RELATIONSHIP_CODES)
    .def_readwrite("TYPE", &OrganizationContentClassification::TYPE)
    .def_readwrite("LOE", &OrganizationContentClassification::LOE)
    .def_readwrite("CLASSIFICATION_ID", &OrganizationContentClassification::CLASSIFICATION_ID)
    .def_readwrite("PUBLIC_LISTED", &OrganizationContentClassification::PUBLIC_LISTED)
    .def_readwrite("LOE_PER", &OrganizationContentClassification::LOE_PER)
    .def_readwrite("REPORTING_TYPE", &OrganizationContentClassification::REPORTING_TYPE);

  py::class_<ConfigReport>(m, "ConfigReport")
    .def(py::init())
    .def_readwrite("status", &ConfigReport::status)
    .def_readwrite("print_form", &ConfigReport::print_form)
    .def_readwrite("drill_down", &ConfigReport::drill_down)
    .def_readwrite("assignee_data_auto_reference", &ConfigReport::assignee_data_auto_reference)
    .def_readwrite("goals", &ConfigReport::goals);

  py::class_<ConfigReportGoals>(m, "ConfigReportGoals")
    .def(py::init())
    .def_readwrite("velocity", &ConfigReportGoals::velocity)
    .def_readwrite("pendingCount", &ConfigReportGoals::pendingCount);

  // Dashboard
  py::class_<Dashboard>(m, "Dashboard")
    .def(py::init<int, const std::string&, const std::string&, const std::string&>())
    .def_readwrite("organization_id", &Dashboard::organization_id)
      //.def_readwrite("user_list", &Dashboard::user_list)
    .def_readwrite("integration_type", &Dashboard::integration_type)
    .def_readwrite("user_number", &Dashboard::user_number)
    .def_readwrite("start_date", &Dashboard::start_date)
    .def_readwrite("end_date", &Dashboard::end_date)
    .def_readwrite("pendingCount_by", &Dashboard::pendingCount_by)
    .def_readwrite("start_cut_date", &Dashboard::start_cut_date)
    .def_readwrite("user_data", &Dashboard::user_data)
    .def_readwrite("user_id_list", &Dashboard::user_id_list)
    .def_readwrite("team_data", &Dashboard::team_data)
    .def_readwrite("task_lightGBMPrediction_list", &Dashboard::task_level_lightGBMPrediction_list)
    .def_readwrite("assigned_tasksRecords", &Dashboard::assigned_tasksRecords)
    // Not needed, only user_data, team_data, task_level_lightGBMPrediction_list
      //.def_readwrite("user_team_details", &Dashboard::user_team_details)
      //.def_readwrite("organization_content", &Dashboard::organization_content)
    .def_readwrite("tags", &Dashboard::tags)
    .def_readwrite("configReport", &Dashboard::configReport)
    .def_readwrite("velocity_goal", &Dashboard::velocity_goal)
    .def_readwrite("rate_goal", &Dashboard::rate_goal)
    .def_readwrite("num_days", &Dashboard::num_days)
    .def_readwrite("project", &Dashboard::project)
    //.def_readwrite("task_index", &Dashboard::task_index)
    .def_readwrite("NOW", &Dashboard::NOW)
    .def_readwrite("user_ids_list", &Dashboard::user_ids_list)
    .def_readwrite("project_level_keys", &Dashboard::project_level_keys)
    .def_readwrite("task_level_keys", &Dashboard::task_level_keys)
    .def_readwrite("user_list", &Dashboard::user_list)
    .def("addUserIdIfNotExist", &Dashboard::addUserIdIfNotExist)
    .def("getUserById", &Dashboard::getUserById)
    .def("appendToUserIdsList", &Dashboard::appendToUserIdsList)
    .def("getUserIdFromUserIdList", &Dashboard::getUserIdFromUserIdList)
    .def("addUserData", &Dashboard::addUserData)
    .def("addTeamData", &Dashboard::addTeamData)
    .def("populateUserDataFromJsonStr", &Dashboard::populateUserDataFromJsonStr)
    .def("populateTeamDataFromJsonStr", &Dashboard::populateTeamDataFromJsonStr)
    .def("populateOrganizationContentTagsFromJsonStr", &Dashboard::populateOrganizationContentTagsFromJsonStr)
    .def("populateProjectFromJsonStr", &Dashboard::populateProjectFromJsonStr);
}
