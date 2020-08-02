# this will compile tenthreads.c file and create an executible called tenthreads. 
#It also has the option to clean the executable and object files.

tenthreads:	tenthreads.c
		/usr/lib64/openmpi/bin/mpicc -O -o tenthreads tenthreads.c

clean:
	rm -f *.exe *.o *~ tenthreads