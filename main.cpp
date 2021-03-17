#include "include/Decoder.h"
#include "include/Encoder.h"
#include "include/FileData.hpp"
#include "include/FileReader.h"
#include "include/FileWriter.h"

#include <gtkmm.h>

int main(int argc, char *argv[]) {

	FileData<char> fd = FileReader::read_ascii_file("../tests/smalltest.txt");
	FileData<uint8_t> encoded = Encoder::encode(fd);

	FileData<char> t = Decoder::decode(encoded);

	//	auto app = Gtk::Application::create("org.pdc");
	//	Gtk::Window window;
	//	window.set_title("Arithmetic Coding");
	//	window.set_default_size(400, 400);
	//
	//	return app->run(window);

	// for (auto &i : fd.data){
	// 	std::cout << i;
	// }

	//	FileWriter::write_ascii_file(fd, "../tests/testwritefile.txt");
}