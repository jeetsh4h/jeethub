#include <iostream>
using namespace std;

#include "employee.h"
#include "load_file.h"

employee records[500] = {employee()};

double avgSalaryID(employee records[], string jobID, int numRecord) {
  double avgSalary = 0.0;
  double count = 0.0;
  for (int i = 0; i < numRecord; i++) {
    if (records[i].job_id == jobID) {
      avgSalary += records[i].salary;
      count++;
    }
  }
  avgSalary /= count;
  return avgSalary;
}

void ManagerDeets(employee records[], int ID) {
  int i = 0;
  while (records[i].id != ID) { i++; }
  employee current = records[i];

  i = 0;
  while (records[i].id != current.manager_id) { i++; }
  records[i].PrintEmployee();
}

int main() {
  int numRecord = load(records);

  cout << avgSalaryID(records, "IT_PROG", numRecord) << endl << endl;
  ManagerDeets(records, 103); cout << endl;
  ManagerDeets(records, 102);
}