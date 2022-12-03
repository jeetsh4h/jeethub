#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
using std::string;

class employee {
public:
  int id;
  string first_name;
  string last_name;
  string job_id;
  int salary;
  int manager_id;

  employee();
  employee(int ID, string F_NAME, string L_NAME, string JOB_ID, int SAL,
           int MAN_ID);

  void PrintEmployee();
};

#endif