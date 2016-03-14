#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Vehicle {
	private:
		int numberOfWheels = 0;
		int numberOfDoors = 0;
		string name	= "Unnamed";
		string typeName = "Vehicle";

	public:
		Vehicle(string name, int numberOfWheels, int numberOfDoors) : 
			name(name), numberOfDoors(numberOfDoors), numberOfWheels(numberOfWheels) {};
		Vehicle(string name);
		Vehicle();
		~Vehicle();
		string toString();
};

Vehicle::Vehicle(string name) {
	this -> name = name;
};
Vehicle::Vehicle() {};
Vehicle::~Vehicle() {};
string Vehicle::toString() {
	return "The " + name + " " + typeName + " has " + to_string(numberOfWheels) + " wheels and " + to_string(numberOfDoors) + " doors.";
}

void main() {	
	Vehicle v;
	cout << v.toString() << endl;

	Vehicle v2 = "Special One";
	cout << v2.toString() << endl;

	Vehicle v3{ "Uniform" };
	cout << v3.toString() << endl;

	Vehicle v4{ "Uniform 2", 4, 4 };
	cout << v4.toString() << endl;

	Vehicle v5 = { "POD-like", 2, 6 };
	cout << v5.toString() << endl;
	
	char charArray[5] = { 'a', 'b', 'c', 'd', 'e' };
	char firstLetter = *charArray;

	cout << "first letter: " << firstLetter << ", is at " << &firstLetter << endl;
	cout << "array is at " << &charArray << endl;
	cout << "secound letter is " << *(charArray+1) << endl;
	cout << endl;

	int* pMyInt = new int;	
	int  vMyInt = *pMyInt;

	vMyInt = 7;

	delete pMyInt;
	

	cout << "pMyInt=" << pMyInt << " vMyInt=" << vMyInt << endl;


	

	int x;
	cin >> x;

}