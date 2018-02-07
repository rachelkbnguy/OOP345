/********************************
NAME: Rachel Khai Binh Nguy
Date: 09/11/2017
STudent: 126463165
Week: 1
********************************/
#include <iostream>

using namespace std;
const int MAX = 3;
namespace w1 {
	char * strncpy(char *DEST, const char *SRC, size_t n) {
		size_t i;
		for (i = 0; i < n && SRC[i] != '\0'; i++)
			DEST[i] = SRC[i];
		for (; i < n; i++)
			DEST[i] = '\0';
		return DEST;
	}
	class Cstring {
		char str[MAX + 1];//+1 for '/0'
	public:
		Cstring(char* s) {
			strncpy(str, s, MAX);
			str[MAX] = '\0';
		}

		void display(ostream& os) {
			os << str;
		}
	};//class Cstring
}//namespace w1
	ostream& operator<<(ostream& os, w1::Cstring& cs) {
		static int count = 0;
		cout << count << ": ";
		cs.display(os);
		count++;
		return os;
	}
	void process(char* s) {
		w1::Cstring cs(s);
		cout << cs << "\n";
	}


int main(int argc, char* argv[]) {
	if (argc == 1) {
		cout << "Command Line: ";
		cout << argv[0];
		cout << '\n';
		cout << "Insufficient number of arguments(min 1)";
		cout << endl;
		return 1;
	}
	else {
		cout << "Command Line: ";
		for (int i = 0; i < argc; i++)
			cout << argv[i] << " ";
		cout << endl;
		cout << "Maximum number of characters stored : " << argc;
		cout << endl;
		for (int i = 1; i < argc; i++)
			process(argv[i]);
		cout << endl;
	}
		
	
	return 0;
}