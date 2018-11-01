test_cpu_temp: prepare_dirs main.cpp get_cpu_temp/get_cpu_temp.cpp get_cpu_temp/get_cpu_temp.h
	g++ -lpthread -o bin/test_cpu_temp main.cpp get_cpu_temp/get_cpu_temp.cpp

prepare_dirs:
	@if [ ! -d bin ]; then mkdir bin; fi;

run: test_cpu_temp
	bin/test_cpu_temp

clean:
	rm bin/*
