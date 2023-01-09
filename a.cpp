#include <iostream>
using namespace std;

class Parent {
    protected:
        string name;
    public:
        Parent(string n=""){
            name = n;
        }
        ~Parent() {
            cout << "Destory Parent object" << endl;
        }
};

class Child : public Parent {
    private:
        int age;
    public:
        Child(int a = 0, string n= "") : Parent(n) {
            age = a;
        }
        ~Child() {
            cout << "Destory Child object" << endl;
        }
};

int main() {
    Parent *ptr;
    ptr = new Child(10, "John");

    delete ptr;

    return 0;
}