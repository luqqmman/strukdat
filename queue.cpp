#include <iostream>
using namespace std;

class Node {
	public:
		int data;
		Node* next;

		Node(int d){
			data = d;
			next = nullptr;
		}
};

class Queue {
	public:
		Node* head;
		Node* tail;

		Queue(void){
			head = nullptr;
		}

		void enqueue(int data){
			Node* n = new Node(data);
			if (head == nullptr){
				n->next = nullptr;
				head = tail = n;
			} else {
				tail->next = n;
				tail = n;
			}
		}

		int dequeue(void){
			Node* n = head;
			head = n->next;
			int tmp = n->data;
			delete n;
			return tmp;
		}

		void print(Node* n){
			if (n == nullptr) return;
			cout << n->data << endl;
			return print(n->next);
		}

		~Queue(void){
			for (Node* n = head; n != nullptr; n = head){
				head = head->next;
				delete n;
			}
		}
};

int main(void){
	Queue q = Queue();
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	
	q.print(q.head);
	return 0;
}
