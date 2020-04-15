#include <Python.h>
#include <assert.h>

int main(int argc, char** argv)
{
	PyObject* asyncio;
	PyThreadState* threadState;
	PyThreadState* subinterpreter;

	Py_Initialize();
	PyEval_InitThreads();

	threadState = PyThreadState_Get();
	subinterpreter = Py_NewInterpreter();

	asyncio = PyImport_ImportModule("asyncio");
	assert(asyncio);
	Py_DECREF(asyncio);

	Py_EndInterpreter(subinterpreter);
	PyThreadState_Swap(threadState);

	asyncio = PyImport_ImportModule("asyncio");
	assert(asyncio);
	Py_DECREF(asyncio);
	
	Py_Finalize();
}
