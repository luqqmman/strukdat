#include "strukdat.hpp"

// Node
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

// Queue
Queue::Queue(void){
	head = nullptr;
}

void Queue::add(Node* n){
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

Node* Queue::get(void){
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

// Stack
Stack::Stack(void){
	head = nullptr;
}

void Stack::add(Node* n){
	if (head == nullptr){
		n->next = nullptr;
		head = tail = n;
	} else {
		Node* tmp = head;
		head = n;
		n->next = tmp;
	}
}

bool Stack::is_empty(void){
	return head == nullptr;
}

Node* Stack::get(void){
	Node* n = head;
	head = n->next;
	return n;
}

Node* Stack::begin(void){
	return head;
}

Node* Stack::end(void){
	return tail;
}

Stack::~Stack(void){
	for (Node* n = head; n != nullptr; n = head){
		head = head->next;
		delete n;
	}
}

