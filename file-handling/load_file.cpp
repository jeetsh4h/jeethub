#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

#include "employee.h"

int load(employee records[]) {
  ifstream input_file;
  input_file.open("employees.csv");

  string record;
  int i = 0;

  stringstream X;
  string temp;
  string tempstr;

  
  getline(input_file, record);
  while(getline(input_file, record)) {
    X << record;
    
    getline(X, tempstr, ',');
    records[i].id = stoi(tempstr);

    getline(X, records[i].first_name, ',');

    getline(X, records[i].last_name, ',');

    getline(X, temp, ',');    // email
    getline(X, temp, ',');    // phone number
    getline(X, temp, ',');    // hire date

    getline(X, records[i].job_id, ',');

    getline(X, tempstr, ',');
    records[i].salary = stoi(tempstr);
    
    getline(X, temp, ',');    // commission pct

    getline(X, tempstr, ',');
    if (!(tempstr == " - ")) {
      records[i].manager_id = stoi(tempstr);
    } else {
      records[i].manager_id = 0;
    }

    getline(X, temp, ',');    // department id

    i++;
    X.clear();
  }

  return i;
}