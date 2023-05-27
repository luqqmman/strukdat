#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <system_error>
#include <vector>
#include <stdlib.h>
#include "strukdat.hpp"
#include "setting.hpp"

// #include <unistd.h> // for linux
// #include <windows.h> // for windows
using namespace std;

/* Variabel global */
int size_x, size_y;
Node start_pos, finish_pos;
vector<vector<bool>> visited;
vector<vector<Node>> backtracker;


/* fungsi driver */
void print_queue(Node* n);
void print_map(vector<vector<char>>& m);
void print_logo();


int main(void){
	/* Buka file MAP */
	print_logo();                                
	cout << "Enter filename: ";
	string filename;
	cin >> filename;
	ifstream f{filename};
	string buffer;


	/* gagal membuka file -> exit program */
	if (!f){
		cout << "gagal membuka " << filename << endl; 
		return -1;
	}

	/* Baca file dan masukan isinya ke vector2d m */
	/* Deklarasikan MAP sebagai vector 2 dimensi */ 
	vector<vector<char>> m, bm;
	for (int i = 0; f; i++){
		/* buat vector1d untuk merepresentasikan row dalam MAP */
		vector<char> v;

		/* baca line dari file ke vector */
		getline(f, buffer);

		for (int j = 0; j < buffer.size(); j++) {
			/* masukan per karakter ke line */
			v.push_back(buffer[j]);

			/* cek apakah sesuai karakter awal atau akhir -> set posisi awal akhir */
			if (buffer[j] == START) start_pos.set(i, j);
			if (buffer[j] == FINISH) finish_pos.set(i, j);
		}
		/* masukan line ke MAP */
		m.push_back(v);
	}
	/* buang row berlebih karena EOF */
	m.pop_back();

	/* buat backup MAP ke vector2d bm */
	bm = m;

	/* simpan ukuran MAP */
	size_x = m[0].size();
	size_y = m.size();

	/* isi vector2d visited dan vector2d backtracker sesuai dengan size */ 
	for (int i = 0; i < size_y; i++){
		vector<bool> vb(size_x, false);
		vector<Node> vn(size_x);
		visited.push_back(vb);
		backtracker.push_back(vn);
	}

	// Mode
	int mode = 0;
	do {
		cout << "1. BFS (for shortest path)" << endl;
		cout << "2. DFS (for random path)" << endl;
		cout << "select 1 or 2: ";
		cin >> mode;
	} while (mode != 1 && mode != 2);
	
	LinkedList* container;
	if (mode == 1) container = new Queue();
	else container = new Stack();
	
	/* buat queue lalu masukan node yang menunjukan posisi awal */
	Node* n = new Node(start_pos.x, start_pos.y);
	container->add(n);

	/* explore MAP sampai queue kosong atau posisi akhir ditemukan */
	while (!container->is_empty()){
		/* evaluasi posisi terbaru */
		Node* position = container->get();

		/* hentikan loop jika posisi terbaru adalah posisi akhir yang dicari */
		if (*position == finish_pos) break;

		/* tandai posisi telah di kunjungi dengan vector2d visited */ 
		visited[position->x][position->y] = true;

		/* tandai posisi terbaru di MAP lalu print MAP */
		m[position->x][position->y] = VISITED;
		print_map(m);

		/* deklarasi posisi terdekat | kanan, kiri, atas, bawah */
		Node nearby_position[] = {
			{position->x - 1, position->y},
			{position->x + 1, position->y},
			{position->x, position->y - 1},
			{position->x, position->y + 1},
		};

		/* cek semua posisi terdekat apakah valid, pernah dikunjungi, atau tidak bisa di explore */
		for (const auto& pos : nearby_position){
			if (pos.x < 0) continue;
			if (pos.y < 0) continue;
			if (pos.x >= size_x) continue;
			if (pos.x >= size_y) continue;
			if (m[pos.x][pos.y] == WALL) continue;
			if (visited[pos.x][pos.y]) continue;

			/* posisi valid -> masukan posisi terbaru sebagai parent dari posisi terdekat */
			backtracker[pos.x][pos.y] = *position;

			/* tandai telah dikunjungi agar tidak ada posisi yang sama di queue */
			visited[pos.x][pos.y] = true;

			/* masukan posisi terdekat ke queue untuk di evaluasi */
			container->add(new Node(pos.x, pos.y));
		}
		delete position;
	}

	/* buat posisi akhir sebagai posisi sekarang */
	Node position = finish_pos;
	int shortest = 0;

	/* gunakan vector2d backtracker untuk kembali ke posisi awal */ 
	while (!(position == start_pos)){
		/* hitung langkah yang diperlukan */
		shortest++;

		/* tandai pergerakan posisi di MAP */
		bm[position.x][position.y] = SHORTEST;
		print_map(bm);

		/* ubah posisi sekarang menjadi posisi parent sesuai hasil explorasi map */
		position = backtracker[position.x][position.y];
	}

	/* print MAP hasil pencarian dan langkah yang dibutuhkan */
	cout << "\n\n---------------------------------------------------------\n\n";
	print_logo();
	bm[finish_pos.x][finish_pos.y] = FINISH;
	print_map(bm);
	
	if (mode == 1) cout << "shortest path: " << shortest << endl;
	else cout << "random path: " << shortest << endl;
	cout << "\n\n---------------------------------------------------------\n\n";

}

/* fungsi debug untuk print isi queue */
void print_queue(Node* n){
	if (n == nullptr) return;
	cout << n->x << " " << n->y << endl;
	print_queue(n->next);
}


/* fungsi untuk print isi MAP */
void print_map(vector<vector<char>>& m){
	// usleep(DELAY); // for linux
	// Sleep(DELAY); // for windows
	for (const auto& line : m){
		for (const  auto& c : line) cout << c;
		cout << endl;
	}
	cout << endl;
}

void print_logo(){
	cout << " ____       _   _       _____ _           _           \n";
	cout << "|  _ \\ __ _| |_| |__   |  ___(_)_ __   __| | ___ _ __ \n";
	cout << "| |_) / _` | __| '_ \\  | |_  | | '_ \\ / _` |/ _ \\ '__|\n";
	cout << "|  __/ (_| | |_| | | | |  _| | | | | | (_| |  __/ |   \n";
	cout << "|_|   \\__,_|\\__|_| |_| |_|   |_|_| |_|\\__,_|\\___|_|   \n\n";
}