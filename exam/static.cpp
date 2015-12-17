#include <iostream>

class Student {
    public:
        static int numStudents;
        Student() {
            numStudents++;
        }
};

class Coop : public Student {
    public:
        Coop() {
            numStudents++;
        }
};

int Student::numStudents = 0;

static void printNumStudents() {
    std::cout << Student::numStudents << std::endl;
}

int main() {
    Student s;
    printNumStudents();
    Coop c;
    printNumStudents();
}
