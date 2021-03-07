#include <gtkmm.h>
#include "include/common.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

int main(int argc, char *argv[]) {
	const std::string s = "my name is junaid";
	std::unordered_map<char, double> m;

	for(char c : s) {
		double count = std::count(s.begin(), s.end(), c);
		double prob = count / s.size();
		m[c] = prob;
	}

	NumberLine nL(m);

//	for(auto& x: nL.line) {
//		std::cout << "[ " << std::setw(5) << x.first << " ] " << x.second << std::endl;
//	}
//
//	auto app = Gtk::Application::create("org.pdc");
//
//	Gtk::Window window;
//	window.set_title("Arithmetic Coding");
//	window.set_default_size(400, 400);
//
//	return app->run(window);
}