all:clen build run

build:
	cl/c test.cpp binary_tree.cpp
	lib binary_tree.obj
	link test.obj binary_tree.lib

clean:
	del *.obj
	del *.exe

run:
	test