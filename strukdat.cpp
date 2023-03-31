#include "strukdat.hpp"

Node::Node(void){
	x = 0;
	y = 0;
	next = nullptr;
}

Node::Node(int a, int b){
	x = a;
	y = b;
	next = nullptr;
}

void Node::set(int a, int b){
	x = a;
	y = b;
}


bool Node::operator==(const Node& other){
	return x == other.x && y == other.y;
}

Queue::Queue(void){
	head = nullptr;
}

void Queue::enqueue(Node* n){
	if (head == nullptr){
		n->next = nullptr;
		head = tail = n;
	} else {
		tail->next = n;
		tail = n;
	}
}

bool Queue::is_empty(void){
	return head == nullptr;
}

Node* Queue::dequeue(void){
	Node* n = head;
	head = n->next;
	return n;
}

Node* Queue::begin(void){
	return head;
}

Node* Queue::end(void){
	return tail;
}

Queue::~Queue(void){
	for (Node* n = head; n != nullptr; n = head){
		head = head->next;
		delete n;
	}
}

