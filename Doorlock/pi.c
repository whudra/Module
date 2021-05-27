#include <Python.h>
/*
int main(void){
	Py_Initialize();
	PyRun_SimpleString("from picamera import PiCamera");
	PyRun_SimpleString("from time import sleep");
	PyRun_SimpleString("camera = PiCamera()");
	PyRun_SimpleString("camera.start_preview()");
	PyRun_SimpleString("sleep(3)");
	PyRun_SimpleString("camera.capture('/home/pi/project/ExampleProgram/Doorlock/testimage.jpg')");
	PyRun_SimpleString("camera.stop_preview()");
	Py_Finalize();
	
	return 0;
}*/

int initCamera(void){
		Py_Initialize();
		PyRun_SimpleString("from picamera import PiCamera");
		PyRun_SimpleString("from time import sleep");
		PyRun_SimpleString("camera = PiCamera()");
		PyRun_SimpleString("camera.start_preview()");
		PyRun_SimpleString("sleep(3)");
		PyRun_SimpleString("camera.capture('/home/pi/project/ExampleProgram/Doorlock/testimage_0526.jpg')");
		PyRun_SimpleString("camera.stop_preview()");
		Py_Finalize();

}
