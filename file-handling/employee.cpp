#include "employee.h"
using std::cout;
using std::endl;

employee::employee() {
  id = 0;
  first_name = "";
  last_name = "";
  job_id = "";
  salary = 0;
  manager_id = 0;
}

employee::employee(int ID, string F_NAME, string L_NAME, string JOB_ID, int SAL,
                   int MAN_ID) {
  id = ID;
  first_name = F_NAME;
  last_name = L_NAME;
  job_id = JOB_ID;
  salary = SAL;
  manager_id = MAN_ID;
}

void employee::PrintEmployee() {
  cout << "Employee ID: " << id << endl;
  cout << "Name: " << first_name << ' ' << last_name << endl;
  cout << "Job ID: " << job_id << endl;
  cout << "Salary: " << salary << endl;
  if (manager_id == 0) {
    cout << "No Manager\n";
  } else {
    cout << "Their Manager's ID: " << manager_id << endl;
  }
}