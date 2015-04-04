tool_test: tool_test.cpp ../../src/Tool.cpp ../../src/Tool.h
	g++ ../../src/Tool.cpp -c
	g++ tool_test.cpp -std=c++11 Tool.o -o tool_test.out

clear:
	rm Tool.o tool_test.out
