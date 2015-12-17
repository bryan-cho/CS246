#include <iostream>

class Book {
    public:
        void sayHello() {
            std::cout << "Hi I'm a book" << std::endl;
        }
};

class TextBook : public Book {
    public:
        void sayHello() {
            std::cout << "Hi I'm a textbook" << std::endl;
        }
};

void sayHelloTB(TextBook& t) {
    t.sayHello();
}

void sayHello(Book& b) {
    b.sayHello();
}

int main () {
    Book b;
    b.sayHello();
    TextBook t;
    t.sayHello();
    sayHello(t);
    sayHelloTB(t);
    Book* pb = new TextBook();
    pb->sayHello(); 
    delete pb;
}

