#include "include/Decoder.h"
#include "include/Encoder.h"
#include "include/FileData.hpp"
#include "include/FileReader.h"
#include "include/FileWriter.h"
#include "include/NumberLine.h"

#include <gtkmm.h>

Gtk::Window *mainWindow = nullptr;
Gtk::FileChooserButton *asciiFileButton = nullptr;
Gtk::FileChooserButton *nullFileButton = nullptr;
Gtk::Button *compressButton = nullptr;
Gtk::Button *decompressButton = nullptr;
Gtk::Label *outputLabel = nullptr;
Glib::RefPtr<Gtk::Application> app;

void compressButtonHandler() {
	std::string filePath = asciiFileButton->get_filename();

	size_t found = filePath.find_last_of('/');
	std::string folder = filePath.substr(0, found);

	FileData<char> fd = FileReader::read_ascii_file(filePath);
	FileData<uint16_t> encoded = Encoder::encode(fd);
	FileWriter::write_bin_file(encoded, folder + "/compressed.null");

	outputLabel->set_text("compressed.null file written to" + folder);
}

void decompressButtonHandler() {
	std::string filePath = nullFileButton->get_filename();

	size_t found = filePath.find_last_of('/');
	std::string folder = filePath.substr(0, found);

	// @Rohan - Implement read_bin_file
	FileData<uint16_t> fd = FileReader::read_bin_file(filePath);
	FileData<char> decoded = Decoder::decode(fd);
	FileWriter::write_ascii_file(decoded, folder + "/decompressed.txt");
	outputLabel->set_text("decompressed.txt file written to" + folder);
}

void on_app_activate() {
	auto refBuilder = Gtk::Builder::create();
	try {
		refBuilder->add_from_file("../ac-gui.glade");
	} catch (const Glib::FileError &ex) {
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	} catch (const Glib::MarkupError &ex) {
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return;
	} catch (const Gtk::BuilderError &ex) {
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}

	refBuilder->get_widget<Gtk::Window>("MainWindow", mainWindow);
	if (!mainWindow) {
		std::cerr << "Could not get the window" << std::endl;
		return;
	}

	refBuilder->get_widget<Gtk::FileChooserButton>("ASCII_input", asciiFileButton);
	refBuilder->get_widget<Gtk::FileChooserButton>("NULL_input", nullFileButton);
	refBuilder->get_widget<Gtk::Button>("compress", compressButton);
	refBuilder->get_widget<Gtk::Button>("decompress", decompressButton);
	refBuilder->get_widget<Gtk::Label>("output", outputLabel);

	// Attaching functions to the compress and decompress buttons
	if (compressButton && decompressButton) {
		compressButton->signal_clicked().connect(sigc::ptr_fun(&compressButtonHandler));
		decompressButton->signal_clicked().connect(sigc::ptr_fun(&decompressButtonHandler));
	} else {
		std::cout << "Button Initialisation Failed" << std::endl;
	}

	if (outputLabel) {
		outputLabel->set_text("No File Selected");
	}

	mainWindow->signal_hide().connect([]() { delete mainWindow; });
	app->add_window(*mainWindow);
	mainWindow->set_title("PDC Project - Arithmetic Coding");
	mainWindow->show();
}

int main(int argc, char *argv[]) {
//	FileData<char> fd = FileReader::read_ascii_file("../tests/testfile.txt");
//	FileData<uint16_t> encoded = Encoder::encode(fd);
//	FileData<char> t = Decoder::decode(encoded);

	app = Gtk::Application::create("pdc.arithmetic-coding");
	app->signal_activate().connect([]() { on_app_activate(); });

	return app->run(argc, argv);
}