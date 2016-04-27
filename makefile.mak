all: main.cpp move.cpp move.h simon.cpp simon.h
	g++ -o simon main.cpp move.cpp simon.cpp `pkg-config gtkmm-3.0 --cflags --libs`