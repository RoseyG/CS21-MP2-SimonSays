#ifndef __simon__
#define __simon__

#include<string.h>
#include<gtkmm.h>
#include"move.h"

class Simon: public Gtk::Window{
	private:
	Gtk::Image *greenW;
	Gtk::Image *redW;
	Gtk::Image *yellowW;
	Gtk::Image *blueW;
	Gtk::Image *whiteW;
	Gtk::Grid game;
	Gtk::Button green_b;
	Gtk::Button blue_b;
	Gtk::Button red_b;
	Gtk::Button yellow_b;
	Gtk::Button game_b;
	Gtk::Button colorSeq;
	Gtk::Label gameScore;
	Gtk::Label colorWatch;
	Gtk::Label instruct;
	std::string scoreStr;
	Move *moves;
	Move *curr;
	Move *temp;
	Move *end;
	bool start;
	bool play;
	int score;
	void addMove();
	void showMove();
	void deleteMoves();
	void onClick(int);
	void on_play();
	void round();
	void switchC(int);
	public:
	Simon();
};

#endif