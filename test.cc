#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "RDD.h"

#define MAX_SIZE  100000
#define MAX_LEN		30
using namespace std;

bool word_in(string str)
{
	if(strstr(str.c_str(),"happy")!=NULL){
		return true;
	}
}

void gen_file()
{
	string s1="this is a happy day";
	string s2="this is a bad day";
	ofstream out("tmp.txt");
	//ifstream in("tmp.txt");
	string str;
	int size=0;
	//while(!in.eof()){
	//	getline(in,str);
		
	//	size+=str.length();
	//	if(size>=1<<14)
	//		break;
			//4 000 000
	//	cout<<str<<endl;
	//}
	for(int i=0;i<MAX_SIZE;i++){
		if(i%2==0){
			out<<s1.c_str()<<"\n";
		}else{
			out<<s2.c_str()<<"\n";
		}
	}
	out.close();
}

int main()
{
	gen_file();
	RDD rdd;
	rdd.text_file("tmp.txt",1<<14);
	//rdd.lazy_read();
	//rdd.debug();
	rdd.filter(&word_in);
	cout<<rdd.count()<<endl;
	return 0;
}
