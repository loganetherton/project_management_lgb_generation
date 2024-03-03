//
// Created by Logan Etherton on 6/15/22.
//

#ifndef PYBIND_JSONOBJECTS_H
#define PYBIND_JSONOBJECTS_H

const char *configReportJson() {
  return R"(
  {
    "status": "active", "print_form": "inactive", "drill_down": "active", "assignee_data_auto_reference": "active",
    "tasks": {
        "201607": {"velocity": 10, "pendingCount": 5000}, "201608": {"velocity": 12, "pendingCount": 20000},
        "201609": {"velocity": 12, "pendingCount": 15000}, "201610": {"velocity": 12, "pendingCount": 20000},
        "201611": {"velocity": 12, "pendingCount": 10000}, "201612": {"velocity": 12, "pendingCount": 8000},
        "201704": {"velocity": 12, "pendingCount": 15000}, "201705": {"velocity": 12, "pendingCount": 15000},
        "201706": {"velocity": 12, "pendingCount": 50000}, "201707": {"velocity": 12, "pendingCount": 45000},
        "201708": {"velocity": 12, "pendingCount": 45000}, "201709": {"velocity": 12, "pendingCount": 45000},
        "201710": {"velocity": 3, "pendingCount": 45000}, "201711": {"velocity": 3, "pendingCount": 20000},
        "201712": {"velocity": 3, "pendingCount": 20000}, "201801": {"velocity": 7, "pendingCount": 20000},
        "201802": {"velocity": 7, "pendingCount": 20000}, "201803": {"velocity": 7, "pendingCount": 28000},
        "201804": {"velocity": 7, "pendingCount": 45000}, "201805": {"velocity": 7, "pendingCount": 50000},
        "201806": {"velocity": 7, "pendingCount": 50000}, "201807": {"velocity": 7, "pendingCount": 50000},
        "201808": {"velocity": 7, "pendingCount": 50000}, "201809": {"velocity": 7, "pendingCount": 50000},
        "201810": {"velocity": 7, "pendingCount": 50000}, "201811": {"velocity": 7, "pendingCount": 40000},
        "201812": {"velocity": 7, "pendingCount": 25000}, "201901": {"velocity": 8, "pendingCount": 25000},
        "_fallback_daily": {"velocity": 8, "pendingCount": 427}
    }
}
)";
}

/**
 * Raw string that we'll convert to JSON to populate user data
 * @return
 */
const char *userDataStr() {
  return R"(
  {
    "0": {"total_count": 0, "eligible_count": 0, "assignee_id": "Unassigned", "pendingCount": 0.0, "success_count": 0,
        "user_id": 0,
        "full_name": "Unassigned", "success_rate": 0, "efficiency_rate": 0, "user_id": 0},
    "1": {"total_count": 2, "eligible_count": 2, "assignee_id": "AMILNE", "pendingCount": 0.0, "success_count": 0, "user_id": 1,
        "full_name": "Unassigned", "success_rate": 0, "efficiency_rate": 0, "user_id": 0},
    "2": {"total_count": 1, "eligible_count": 1, "assignee_id": "CMCCANTS", "pendingCount": 0.0, "success_count": 0,
        "user_id": 2,
        "full_name": "Unassigned", "success_rate": 0, "efficiency_rate": 0, "user_id": 0}
  }
  )";
}

const char *teamDataStr() {
  return R"(
    {"team_total_count": 3, "team_eligible_count": 3, "team_pendingCount": 0,
    "team_average_pendingCount": 0, "team_target_pendingCount": 0, "team_target_count": 0,
    "team_average_count": 0, "team_target_percentage": 0, "team_average_percentage": 0,
    "team_success_count": 0, "team_success_rate": 0, "team_efficiency_rate": 0}
  )";
}

const char *organizationContentTagsStr() {
  return R"(
    {
    "93957": {
        "STATUS": "deleted", "ORDERING_TYPE": "standard", "NAME": "Z16 TBD", "RELATIONSHIP_CODES": [],
        "TYPE": "relationship_lightGBMPrediction", "LOE": 0, "CLASSIFICATION_ID": 93957, "PUBLIC_LISTED": 1, "LOE_PER": "estPoint",
        "REPORTING_TYPE": "relationship_lightGBMPrediction"
    }
}
  )";
}

const char *project1str() {
  return R"(
    {
    "_id": "5e30aacf9ff605b31b797e09", "organization_id": 4877, "creation_id": "1948860.1", "creation": "2020-01-28",
    "updated": "2020-05-21 21:01:26", "last_name": "TestLast", "task_dependencies": 1, "completion_iso": "2020-01-30 00:00:00",
    "creation_status": "Current", "classification_code": "SQB", "avg_loe": 139.5,
    "task_list": {
        "95887": {
            "lightGBMPrediction_end": "2020-01-30", "user_loe": 15, "display_order": 1, "lightGBMPrediction_start": "2020-01-28",
            "user_id": 95358, "classifierPredication_loe": 10, "tasked_date": "2020-01-28 21:54:35", "override_total": 30,
            "displayed": "no", "accepted": "yes", "type": "relationship_lightGBMPrediction",
            "assigned_users": [
                {"date_time": "2020-05-20 18:55:25", "assigned_from": 20661, "assigned_to": 95358,
                 "assigned_by": 23952},
                {"date_time": "2020-05-20 18:57:34", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 20661},
                {"date_time": "2020-05-20 18:57:36", "assigned_from": 20661, "assigned_to": 20661,
                 "assigned_by": 23952},
                {"date_time": "2020-05-20 18:57:49", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 95358},
                {"assigned_by": 23952, "assigned_from": 95358, "assigned_to": 20661,
                 "date_time": "2020-05-20 18:59:09"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 95358, "date_time": "2020-07-01 14:02:50"}
            ],
            "loe_per": "estPoint", "quantity": 1, "assignee_override_total": 30, "projected_assignee_total": 30, "assignee_loe": 15,
            "loe_per_unit": 15
        }
    },
    "taskDependenciesSub": 0, "user_language": "", "first_name": "TestFirst", "estPoints": 2,
    "is_shared": false, "creation_iso": "2020-01-28 00:00:00", "sub_task_code": "SQB", "completion": "2020-01-30",
    "user_email": "", "validationId": "", "los": 2, "relationship_id": 123773, "from_userUpdates": false, "classification_id": 95886,
    "ancillary_list": {}, "status": "assigned", "comments": [], "created": "2020-01-28 21:42:39", "user_id": 95358,
    "accepted_lightGBMPredictions": ["SKB"], "projected_total_pendingCount": 30, "assignee_total_pendingCount": 30, "projected_assignee_pendingCount": 30
}
  )";
}

const char *task2str() {
  return R"(
{
    "_id": "5e3344349ff605b31b797e3f", "organization_id": 4877, "creation_id": "1948860.2", "creation": "2020-01-28",
    "updated": "2020-07-09 20:19:54", "last_name": "TestLast", "task_dependencies": 1, "completion_iso": "2020-01-30 00:00:00",
    "creation_status": "Current", "classification_code": "SQB", "avg_loe": 139.5,
    "task_list": {
        "95887": {
            "lightGBMPrediction_end": "2020-01-30", "user_loe": 19, "display_order": 1, "lightGBMPrediction_start": "2020-01-28",
            "user_id": 95358, "override_total": 38, "tasked_date": "2020-07-09 20:19:54", "classifierPredication_loe": 10,
            "displayed": "no", "accepted": "yes", "type": "relationship_lightGBMPrediction",
            "assigned_users": [
                {"date_time": "2020-05-20 18:56:25", "assigned_from": 95358, "assigned_to": 95358,
                 "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:27", "assigned_from": 95358, "assigned_to": 0, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:33", "assigned_from": 0, "assigned_to": 95358, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:43", "assigned_from": 95358, "assigned_to": 0, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:57:52", "assigned_from": 95358, "assigned_by": 23952,
                 "assigned_to": 20661},
                {"date_time": "2020-05-20 18:58:50", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 95358},
                {"date_time": "2020-05-20 18:58:54", "assigned_from": 95358, "assigned_by": 23952,
                 "assigned_to": 20661},
                {"date_time": "2020-05-20 18:59:01", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 95358},
                {"assigned_by": 95358, "assigned_from": 95358, "assigned_to": 20661,
                 "date_time": "2020-05-21 14:19:36"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 20661,
                 "date_time": "2020-05-21 17:04:46"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-21 17:05:22"},
                {"assigned_by": 95358, "assigned_from": "", "assigned_to": 20661, "date_time": "2020-05-21 17:05:54"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 20661,
                 "date_time": "2020-05-26 13:15:41"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-26 13:15:44"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-26 13:15:45"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-29 15:29:17"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-29 15:29:26"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-29 15:50:42"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-29 15:50:44"},
                {"assigned_by": 95358, "assigned_from": 95358, "assigned_to": 20661, "date_time": "2020-07-01 14:02:45"}
            ],
            "loe_per": "estPoint", "quantity": 1, "projected_assignee_total": 38, "assignee_loe": 19, "loe_per_unit": 19
        }
    },
    "taskDependenciesSub": 0, "user_language": "", "first_name": "TestFirst", "estPoints": 2, "is_shared": false,
    "creation_iso": "2020-01-28 00:00:00", "sub_task_code": "SQB", "completion": "2020-01-30", "user_email": "",
    "validationId": "", "los": 2, "relationship_id": "123773", "from_userUpdates": false, "classification_id": "95886",
    "ancillary_list": {
        "95880": {
            "lightGBMPrediction_end": "2020-07-17", "user_loe": 0, "display_order": 6, "lightGBMPrediction_start": "2020-07-16",
            "override_total": 35, "classifierPredication_loe": 35, "accepted": "no", "type": "early_subTask", "loe_per": "progress",
            "quantity": 1,
            "assigned_users": [
                {"date_time": "2020-05-20 18:55:25", "assigned_from": 20661, "assigned_to": 95358, "assigned_by": 23952}
            ]
        },
        "95887": {
            "lightGBMPrediction_end": "2020-07-20", "user_loe": 0, "display_order": 7, "lightGBMPrediction_start": "2020-07-16",
            "override_total": 200, "classifierPredication_loe": 50, "accepted": "no", "type": "relationship_feature", "loe_per": "estPoint",
            "quantity": 1
        }
    },
    "status": "assigned",
    "comments": [
        {"full_name": "Logan Etherton", "comment": "gewgew", "date_time": "2020-04-30 20:41:20"},
        {"full_name": "Logan Etherton", "comment": "ffff", "date_time": "2020-04-30 20:41:40"},
        {"full_name": "thivya", "comment": "test", "date_time": "2020-05-21 04:19:52"},
        {"full_name": "Logan Etherton", "comment": "fgewwe", "date_time": "2020-06-18 19:54:36"}
    ],
    "created": "2020-01-28 21:42:39", "user_id": 95358, "accepted_lightGBMPredictions": ["SKB"], "projected_total_pendingCount": 38,
    "assignee_total_pendingCount": 38, "projected_assignee_pendingCount": 38
}
)";
}

const char *project3str() {
  return R"(
{
    "_id": "5e3327439ff605b31b797e35", "organization_id": 4877, "creation_id": "1778516.1", "creation": "2020-02-06",
    "updated": "2020-01-30 19:11:49", "last_name": "TestLast", "task_dependencies": 2, "completion_iso": "2020-02-09 00:00:00",
    "creation_status": "Current", "classification_code": "CQB", "avg_loe": 68, "task_list": {}, "taskDependenciesSub": 0,
    "user_language": "", "first_name": "TestFirst", "estPoints": 3, "creation_iso": "2020-02-06 00:00:00", "sub_task_code": "CQB",
    "completion": "2020-02-09", "user_email": "", "validationId": "", "los": 3, "relationship_id": "123771", "from_userUpdates": false,
    "classification_id": "95882", "ancillary_list": {}, "status": "pending", "comments": [], "created": "2020-01-30 19:11:49"
}
)";
}

const char *project4str() {
  return R"(
{
    "_id": "5e3344349ff605b31b979e3f", "organization_id": 4877, "creation_id": "1948861.2", "creation": "2020-01-28",
    "updated": "2020-07-09 20:19:54", "last_name": "TestLast", "task_dependencies": 1, "completion_iso": "2020-01-30 00:00:00",
    "creation_status": "Current", "classification_code": "SQB", "avg_loe": 139.5,
    "task_list": {
        "95887": {
            "lightGBMPrediction_end": "2020-01-30", "user_loe": 19, "display_order": 1, "lightGBMPrediction_start": "2020-01-28",
            "user_id": 95358, "override_total": 38, "tasked_date": "2020-07-09 20:19:54", "classifierPredication_loe": 10,
            "displayed": "no", "accepted": "yes", "type": "relationship_lightGBMPrediction",
            "assigned_users": [
                {"date_time": "2020-05-20 18:56:25", "assigned_from": 95358, "assigned_to": 95358,
                 "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:27", "assigned_from": 95358, "assigned_to": 0, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:33", "assigned_from": 0, "assigned_to": 95358, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:56:43", "assigned_from": 95358, "assigned_to": 0, "assigned_by": 23952},
                {"date_time": "2020-05-20 18:57:52", "assigned_from": 95358, "assigned_by": 23952,
                 "assigned_to": 20661},
                {"date_time": "2020-05-20 18:58:50", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 95358},
                {"date_time": "2020-05-20 18:58:54", "assigned_from": 95358, "assigned_by": 23952,
                 "assigned_to": 20661},
                {"date_time": "2020-05-20 18:59:01", "assigned_from": 20661, "assigned_by": 23952,
                 "assigned_to": 95358},
                {"assigned_by": 95358, "assigned_from": 95358, "assigned_to": 20661,
                 "date_time": "2020-05-21 14:19:36"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 20661,
                 "date_time": "2020-05-21 17:04:46"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-21 17:05:22"},
                {"assigned_by": 95358, "assigned_from": "", "assigned_to": 20661, "date_time": "2020-05-21 17:05:54"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 20661,
                 "date_time": "2020-05-26 13:15:41"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-26 13:15:44"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-26 13:15:45"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-29 15:29:17"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-29 15:29:26"},
                {"assigned_by": 95358, "assigned_from": 20661, "assigned_to": 0, "date_time": "2020-05-29 15:50:42"},
                {"assigned_by": 95358, "assigned_from": 0, "assigned_to": 20661, "date_time": "2020-05-29 15:50:44"},
                {"assigned_by": 95358, "assigned_from": 95358, "assigned_to": 20661,
                 "date_time": "2020-07-01 14:02:45"}
            ],
            "loe_per": "estPoint", "quantity": 1, "projected_assignee_total": 38, "assignee_loe": 19,
            "loe_per_unit": 19
        }
    },
    "taskDependenciesSub": 0, "user_language": "", "first_name": "TestFirst", "estPoints": 2, "is_shared": false,
    "creation_iso": "2020-01-28 00:00:00", "sub_task_code": "SQB", "completion": "2020-01-30", "user_email": "",
    "validationId": "", "los": 2, "relationship_id": "123773", "from_userUpdates": false, "classification_id": "95886",
    "ancillary_list": {
        "95887": {"lightGBMPrediction_end": "2020-01-30", "user_loe": 19, "display_order": 1, "lightGBMPrediction_start": "2020-01-28",
                  "user_id": 95358, "override_total": 38, "tasked_date": "2020-07-09 20:19:54", "classifierPredication_loe": 10,
                  "displayed": "no", "accepted": "yes", "type": "relationship_lightGBMPrediction",
                  "assigned_users": [
                      {"assigned_by": 95358, "assigned_from": 95358, "assigned_to": 20661,
                       "date_time": "2020-07-01 14:02:45"}
                  ],
                  "loe_per": "estPoint", "quantity": 1, "projected_assignee_total": 38, "assignee_loe": 19,
                  "loe_per_unit": 19},
        "95880": {"lightGBMPrediction_end": "2020-07-17", "user_loe": 0, "display_order": 6, "lightGBMPrediction_start": "2020-07-16",
                  "override_total": 35, "classifierPredication_loe": 35, "accepted": "no", "type": "early_subTask",
                  "loe_per": "progress",
                  "quantity": 1,
                  "assigned_users": [
                      {"date_time": "2020-05-20 18:55:25", "assigned_from": 20661, "assigned_to": 95358,
                       "assigned_by": 23952}
                  ]},
        "96165": {"lightGBMPrediction_end": "2020-07-20", "user_loe": 0, "display_order": 7, "lightGBMPrediction_start": "2020-07-16",
                  "override_total": 200, "classifierPredication_loe": 50, "accepted": "no", "type": "relationship_feature",
                  "loe_per": "estPoint",
                  "quantity": 1}},
    "status": "assigned",
    "comments": [
        {"full_name": "Logan Etherton", "comment": "gewgew", "date_time": "2020-04-30 20:41:20"},
        {"full_name": "Logan Etherton", "comment": "ffff", "date_time": "2020-04-30 20:41:40"},
        {"full_name": "thivya", "comment": "test", "date_time": "2020-05-21 04:19:52"},
        {"full_name": "Logan Etherton", "comment": "fgewwe", "date_time": "2020-06-18 19:54:36"}
    ],
    "created": "2020-01-28 21:42:39", "user_id": 95358, "accepted_lightGBMPredictions": ["SKB"], "projected_total_pendingCount": 38,
    "assignee_total_pendingCount": 38, "projected_assignee_pendingCount": 38
}
)";
}

const char *subTaskStr() {
  return R"(
  {
    "_id": "62a36a18e0575cedb2f70e36", "creation": "2020-01-14", "creation_month": "201910",
    "exclusion_reason": "", "organization_id": 4877, "creation_ids": ["1948860.1"], "update_user": "AMILNE",
    "user_id": 1
  }
  )";
}

#endif //PYBIND_JSONOBJECTS_H
