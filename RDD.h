#ifndef RDD_H
#define RDD_H

#include <list>
#include <string>

using namespace std;

class split {
public:
	list<string> elem;
};

class RDD {
public:
	list<split> _split;
	string file_path;
	int split_size;
	bool read_flag;
	RDD();
	void text_file(string file_path, int size);
	RDD &map(void *func);
	RDD &filter(bool (*func)(string));
	RDD &reduce();
	void lazy_read();
	int count();
	void debug();
};

#endif
