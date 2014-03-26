all:
	g++ -c main.cpp
	g++ -o affine main.o -lopencv_core -lopencv_highgui -lopencv_imgproc