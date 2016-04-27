#include<iostream>
#include<gtkmm.h>
#include<time.h>
#include<sstream>
#include"simon.h"
#include"move.h"

/**
This constructs the game.
**/
Simon::Simon(){
	srand(time(NULL));

	add(game);
	
	Gtk::Image *green = new Gtk::Image("green.png");
	Gtk::Image *red = new Gtk::Image("red.png");
	Gtk::Image *yellow = new Gtk::Image("yellow.png");
	Gtk::Image *blue = new Gtk::Image("blue.png");
	greenW = new Gtk::Image("green.png");
	redW = new Gtk::Image("red.png");
	yellowW = new Gtk::Image("yellow.png");
	blueW = new Gtk::Image("blue.png");
	whiteW = new Gtk::Image("white.png");
	
	game_b.set_label("Play!");
	game_b.set_size_request(150,70);
	game_b.signal_clicked().connect(sigc::mem_fun(*this,&Simon::on_play));
	game.attach(game_b,0,0,1,1);
	game_b.show();

	green_b.set_image(*green);
	green_b.set_size_request(150,150);
	green_b.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&Simon::onClick),1));
	game.attach(green_b,2,0,1,2);
	green_b.show();
	green->show();

	red_b.set_image(*red);
	red_b.set_size_request(150,150);
	red_b.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&Simon::onClick),2));
	red_b.show();
	red->show();
	game.attach(red_b,3,0,1,2);

	yellow_b.set_image(*yellow);
	yellow_b.set_size_request(150,150);
	yellow_b.signal_released().connect(sigc::bind<int>(sigc::mem_fun(*this,&Simon::onClick),3));
	yellow_b.show();
	yellow->show();
	game.attach(yellow_b,2,2,1,2);

	blue_b.set_image(*blue);
	blue_b.set_size_request(150,150);
	blue_b.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this,&Simon::onClick),4));
	blue_b.show();
	blue->show();
	game.attach(blue_b,3,2,1,2);

	colorSeq.set_image(*whiteW);
	colorSeq.set_size_request(150,150);
	colorSeq.signal_clicked().connect(sigc::mem_fun(*this,&Simon::round));
	game.attach(colorSeq,0,2,2,2);
	colorSeq.show();

	gameScore.set_label("Score: ");
	gameScore.set_size_request(150,70);
	game.attach(gameScore,1,0,1,1);
	gameScore.show();

	colorWatch.set_label("Click play to start the game.");
	colorWatch.set_size_request(150,70);
	game.attach(colorWatch,0,1,2,1);
	colorWatch.show();

	instruct.set_label("Click the buttons accordng to the colors shown.\nStart with one color, then add the next color shown to the sequnce of buttons to click.");
	instruct.set_size_request(350,70);
	game.attach(instruct,0,4,4,1);
	instruct.show();

	start = false;
	play = false;
	temp = NULL;
	curr = NULL;
	moves = NULL;
	end = NULL;
	game.show();
}
/**
This adds a move to the sequence of buttons.
**/
void Simon::addMove(){
	temp = new Move;
	temp->setValue((rand()%4)+1);
	if(moves == NULL){
		moves = temp;
		end = temp;
	}
	else{
		end->setNext(temp);
		end = end->getNext();
	}
	curr = moves;
}
/**
This shows the next move by switching the color on the colorSeq button.
**/
void Simon::showMove(){
	int x;
	play = false;
	while (curr!=NULL){
		x = curr->getValue();
		curr = curr->getNext();
	}
	switchC(x);
	curr = moves;
	play = true;
}
/**
This empties the list of moves, deleting the sequence.
**/
void Simon::deleteMoves(){
	while (moves!=NULL){
		curr = moves;
		moves = moves->getNext();
		delete curr;
	}
}
/**
This checks if you clicked the right button. Points are added to the score equal to the length of the current sequence. If the wrong button is clicked, you lose the game. The score is set back to zero.
**/
void Simon::onClick(int x){
	if(play){
		if (curr->getValue() != x){
			score = 0;
			deleteMoves();
			play = false;
			start = false;
			game_b.set_label("Play Again");
			colorWatch.set_label("Click Play Again!");
			colorSeq.set_image(*whiteW);
			Gtk::MessageDialog diaLose("You Lose!");
			diaLose.run();
		}
		else
			curr = curr->getNext();
		if(curr == NULL){
			score ++;
			play = false;
			colorSeq.set_image(*whiteW);
			colorWatch.set_label("Good Job! Click for next color!");
		}
		std::ostringstream temp;
		temp<<"Score: "<<score;
		scoreStr = temp.str(); 
		gameScore.set_label(scoreStr);
	}
	else{
		if(start){
			Gtk::MessageDialog diaNext("Click below for the next color!");
			diaNext.run();
		}
		else{
			Gtk::MessageDialog diaPlay("Click play!");
			diaPlay.run();
		}
	}
}
/**
This starts and stops the game.
**/
void Simon::on_play(){
	if(start){
		play = false;
		start = false;
		deleteMoves();
		game_b.set_label("Play");
		colorWatch.set_label("Click Play To Start Again!");
		colorSeq.set_image(*whiteW);
		Gtk::MessageDialog diaStop("You decided to stop the game.");
		diaStop.run();
	}
	else{
		game_b.set_label("Stop");
		Gtk::MessageDialog diaStart("Start!");
		diaStart.run();
		score = 0;
		colorWatch.set_label("Watch me!");
		start = true;
		round();
	}
}
/**
This creates a new round after a new or a successful one in the game.
**/
void Simon::round(){
	if (start)
		if (!play){
			addMove();
			colorWatch.set_label("Here's your color!");
			showMove();
			play = true;
		}
}
/**
This shows the next color in the colorSeq button.
**/
void Simon::switchC(int x){
//	std::string color;
		if (x==1){
			colorSeq.set_image(*greenW);
			greenW->show();
//			color = "GREEN";
		}
		else if (x==2){
			colorSeq.set_image(*redW);
			redW->show();
//			color = "RED";
		}
		else if (x==3){
			colorSeq.set_image(*yellowW);
			yellowW->show();
//			color = "YELLOW";
		}
		else if (x==4){
			colorSeq.set_image(*blueW);
			blueW->show();
//			color = "BLUE";
		}
//		std::cout<<"This is move: "<<color<<std::endl; //For Testing
}