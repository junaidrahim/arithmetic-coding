#include <gtkmm.h>
#include "include/FileReader.h"
#include "include/common.hpp"

int main(int argc, char *argv[]) {

	FileData<char> fd = FileReader::read_ascii_file("../tests/testfile.txt");
//	auto app = Gtk::Application::create("org.pdc");
//	Gtk::Window window;
//	window.set_title("Arithmetic Coding");
//	window.set_default_size(400, 400);
//
//	return app->run(window);
}