
//#-------------------------------------------------------------------
	Py_Initialize() ;
	PyEval_InitThreads() ;
	PyThreadState* pMainThreadState = PyEval_SaveThread() ;
//#-------------------------------------------------------------------


