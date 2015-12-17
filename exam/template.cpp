#include <iostream>

template <typename T>
class Node {
    private:
        T data;
        Node<T> *next;
    public:
        Node<T>();
        Node<T>(T data, Node<T>* next) : data(data), next(next) {};
        ~Node<T>() {
            delete next;
        }
        T getData() {
            return this->data;
        }
        Node<T>* getNext() {
            return this->next;
        }
};

int main() {
    Node<int> *intHead = new Node<int>(1, new Node<int>(2, NULL));
    Node<char> *charHead = new Node<char>('a', new Node<char>('b', NULL));
    Node<int> *head1 = intHead;
    Node<char> *head2 = charHead;
    while (head1 != NULL) {
        std::cout << head1->getData() << std::endl;
        head1 = head1->getNext();
    }
    while (head2 != NULL) {
        std::cout << head2->getData() << std::endl;
        head2 = head2->getNext();
    }
    delete intHead;
    delete charHead;
}

