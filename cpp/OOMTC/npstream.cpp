#include <iostream>
#include <fstream>

using namespace std;

template<class T> class npstream {
	char PipeName[20];
	unsigned long PipeHandle;
	long int PipeMode;
	long int OpenMode;
	long int OutputBufSize;
	long int InputBufSize;
	long int TimeOut;
	unsigned long Result;
	fstream NamedPipe;

public:
	npstream(char *PName, long PMode, long OMode, long TOut = 1000);
	npstream(char *PName);
	ostream &operator<<(T &X);
	istream &operator>>(T &X);
	long int pipeMode(void);
	long int openMode(void);
	long int outBufSize(void);
	long int timeOut(void);
	unsigned long result(void);
};

template<class T> npstream<T>::npstream(char *PName, 
										long PMode, long OMode, long TOut = 1000) {

	strcpy(PipeName, PName);
	PipeMode = PMode;
	OpenMode = OMode;
	OutputBufSize = (sizeof(T) * 1000);
	InputBufSize = (sizeof(T) * 1000);
	TimeOut = TOut;
	Result = 
}
