#ifndef RDD_H
#define RDD_H

#include <list>
#include <string>

using namespace std;

class split {
  list<string> elem;
};

class RDD {
	list<split> spl;
	RDD();
	RDD &map(void *func);
	RDD &filter(void *func);
	RDD &reduce();
};

#endif
