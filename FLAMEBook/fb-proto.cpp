#include <iostream>
using namespace std;

class FLAMEBookUser {
private:
  string firstName;
  string lastName;
  FLAMEBookUser *(friends[10]);

public:
  FLAMEBookUser(string fName, string lName) {
    firstName = fName;
    lastName = lName;
    for (int i = 0; i < 10; i++) {
      friends[i] = NULL;
    }
  }

  string get_fName() { return firstName; }
  string get_lName() { return lastName; }
  // Prajish: return &friends[0] is the same as return friends
  FLAMEBookUser **get_friends() { return &(friends[0]); }

  void add_friend(FLAMEBookUser *user);
  void print_details();
};

void FLAMEBookUser::add_friend(FLAMEBookUser *user) {
  int i = 0;
  while (this->get_friends()[i] != NULL) {
    i++;
  }
  friends[i] = user;
}

void FLAMEBookUser::print_details() {
  cout << "First Name: " << get_fName() << endl;
  cout << "Last Name: " << get_lName() << endl;
  cout << "\nFriends:\n";

  int i = 0;
  while (get_friends()[i] != NULL) {
    cout << get_friends()[i]->get_fName() << ' '
         << get_friends()[i]->get_lName() << endl;
    i++;
  }
}

void mutual_friends(FLAMEBookUser *user1, FLAMEBookUser *user2) {
  cout << "\nMutual Friends of " << user1->get_fName() << " and "
       << user2->get_fName() << " are:\n";

  int i = 0;
  int j;
  while (user1->get_friends()[i] != NULL) {
    j = 0;
    while (user2->get_friends()[j] != NULL) {
      if (user1->get_friends()[i] == user2->get_friends()[j]) {
        cout << user1->get_friends()[i]->get_fName() << ' '
             << user1->get_friends()[i]->get_lName() << endl;
      }
      j++;
    }
    i++;
  }
}

int main() {
  FLAMEBookUser user1("Bill", "Gates");
  FLAMEBookUser user2("Mark", "Zuckerberg");
  FLAMEBookUser user3("Larry", "Page");
  FLAMEBookUser user4("Aura", "Borealis");
  FLAMEBookUser user5("XYZ", "ABC");
  FLAMEBookUser user6("LMAO", "Cutie");

  user4.add_friend(&user5);
  user5.add_friend(&user4);
  user4.add_friend(&user6);
  user5.add_friend(&user6);

  user1.add_friend(&user2);
  user1.add_friend(&user3);
  user1.print_details();

  user2.add_friend(&user3);

  cout << endl;
  user4.print_details();

  mutual_friends(&user1, &user2);
  mutual_friends(&user4, &user5);
}