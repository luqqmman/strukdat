#pragma once

struct Node {
	int x;
	int y;
	Node* next;

	Node (void);
	Node(int a, int b);
	bool operator==(const Node& other);
	void set(int a, int b);
};

class LinkedList {
	public:
		virtual void add(Node* n) = 0;
		virtual bool is_empty(void) = 0;
		virtual Node* get(void) = 0;
		virtual Node* begin(void) = 0;
		virtual Node* end(void) = 0;
};

class Queue : public LinkedList {
	Node* head;
	Node* tail;

	public:
		Queue(void);
		void add(Node* n);
		bool is_empty(void);
		Node* get(void);
		Node* begin(void);
		Node* end(void);
		~Queue(void);
};

class Stack : public LinkedList {
	Node* head;
	Node* tail;

	public:
		Stack(void);
		void add(Node* n);
		bool is_empty(void);
		Node* get(void);
		Node* begin(void);
		Node* end(void);
		~Stack(void);
};
