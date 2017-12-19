#include <vector>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>
#include <algorithm>
using namespace std;

struct MYFILE
{
	unsigned long fileLength;
};
bool less(const MYFILE& l,const MYFILE& r){
	return l.fileLength < r.fileLength;
}
int 
main(int argc, char* argv[])
{
	vector<MYFILE> v;

	for(int i=9;i>=0;i--){
		MYFILE f;
		f.fileLength = i;
		v.push_back(f);
	}


	for(int i=0;i<10;i++){
		printf("%d\n",v[i].fileLength);
	}
	
	sort(v.begin(),v.end(),less);

	for(int i=0;i<10;i++){
		printf("%d\n",v[i].fileLength);
	}

	exit(0);
}
