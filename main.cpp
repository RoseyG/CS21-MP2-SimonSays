#include<iostream>
#include<gtkmm.h>
#include"simon.h"

int main(int argc, char **argv){
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.examples.base");
	Simon simon;
	simon.set_default_size(300,300);
	return app->run(simon);
}