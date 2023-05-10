#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TabFile.h"
#include "TabFileCustom.h"

using namespace std;

int main()
{
	TabFileCustom tab;
	TabFileCustomCompress* compress = new TabFileCustomCompress();
	compress->Load("test_config.txt");
	compress->Find(1, tab);
	return 0;
}
