svdcmp.o: svdcmp.c
	gcc -c -g svdcmp.c 

svbksb.o: svbksb.c
	gcc -c -g svbksb.c

solve_system.o: svdcmp.o svbksb.o solve_system.c 
	gcc -c -g solve_system.c

Test: solve_system.o Test.cpp
	g++ -g -Wno-deprecated -o Test svdcmp.o svbksb.o solve_system.o Test.cpp
