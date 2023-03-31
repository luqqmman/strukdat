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

class Queue {
	Node* head;
	Node* tail;

	public:
		Queue(void);
		void enqueue(Node* n);
		bool is_empty(void);
		Node* dequeue(void);
		Node* begin(void);
		Node* end(void);
		~Queue(void);
};
