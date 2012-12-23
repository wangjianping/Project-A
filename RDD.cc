#include "RDD.h"
#include <fstream>
#include <iostream>

RDD::RDD() {
	this->file_path="";
	this->split_size=0;
	this->read_flag=false;
}

RDD &RDD::map(void *func) {
	return *this;
}

RDD &RDD::filter(bool (*func)(string)){
	if(this->read_flag==false){
		lazy_read();
		this->read_flag=true;
	}
	list<split>::iterator iter_split;
	list<string>::iterator iter_elem;
	int elem_erase=0;
	for(iter_split=_split.begin();iter_split!=_split.end();iter_split++){
		for(iter_elem=iter_split->elem.begin();iter_elem!=iter_split->elem.end();advance(iter_elem,1-elem_erase)){
			elem_erase=0;
			if(func(*iter_elem)==false){
				iter_elem=iter_split->elem.erase(iter_elem);
				elem_erase=1;
			}
		}
	}
	return *this;

}

void RDD::text_file(string file_path, int size) {
	this->file_path=file_path;
	this->split_size=size;

}

RDD &RDD::reduce( ){
	return *this;
}

int RDD::count(){
	int count=0;
	list<split>::iterator iter_split;
	for(iter_split=_split.begin();iter_split!=_split.end();iter_split++){
		count+=iter_split->elem.size();
	}
	return count;
}

void RDD::lazy_read(){
	string str;
	int size;
	int _split_num;
	_split_num=0;
	split __split;
	list<string>::iterator it;
	list<split>::iterator its;
	it=__split.elem.begin();
	its=_split.begin();
	ifstream in;
	in.open(this->file_path.c_str(),fstream::in);
	size=0;
	while(!in.eof()){
		getline(in,str);	
		size+=str.length();
		if(size>=this->split_size){
			size=0;
			_split.insert(its++,__split);
			__split.elem.clear();
			it=__split.elem.begin();
			continue;
		}else{
			__split.elem.insert(it,str);
			it++;
		}
	}
}

void RDD::debug(){
	list<split>::iterator iter_split;
	list<string>::iterator iter_elem;
	string tmp;
	for(iter_split=_split.begin();iter_split!=_split.end();iter_split++){
		for(iter_elem=iter_split->elem.begin();iter_elem!=iter_split->elem.end();iter_elem++){
			std::cout<<*iter_elem<<std::endl;
		}
	}
}
