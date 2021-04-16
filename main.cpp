#include "include/Decoder.h"
#include "include/Encoder.h"
#include "include/FileData.hpp"
#include "include/FileReader.h"
#include "include/FileWriter.h"
#include "include/NumberLine.h"

#include <gtkmm.h>

Gtk::Window *pWindow = nullptr;
Gtk::FileChooserButton *aButton = nullptr;
Gtk::FileChooserButton *nButton = nullptr;
Gtk::Button *cButton = nullptr;
Gtk::Button *dButton = nullptr;
Glib::RefPtr<Gtk::Application> app;

void on_button_clicked()
{
	if (pWindow)
		pWindow->hide(); //hide() will cause Gtk::Application::run() to end.
}

void on_app_activate()
{
	// Load the GtkBuilder file and instantiate its widgets:
	auto refBuilder = Gtk::Builder::create();
	try
	{
		refBuilder->add_from_file("../ac-gui.glade");
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		return;
	}
	catch(const Glib::MarkupError& ex)
	{
		std::cerr << "MarkupError: " << ex.what() << std::endl;
		return;
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		return;
	}

	// Get the GtkBuilder-instantiated window:
	refBuilder->get_widget<Gtk::Window>("MainWindow", pWindow);
	if (!pWindow)
	{
		std::cerr << "Could not get the window" << std::endl;
		return;
	}

	// Get the GtkBuilder-instantiated button, and connect a signal handler:
	refBuilder->get_widget<Gtk::FileChooserButton>("ASCII_input", aButton);
	if (aButton){}
	refBuilder->get_widget<Gtk::FileChooserButton>("NULL_input", nButton);
	if (nButton){}

	refBuilder->get_widget<Gtk::Button>("compress", cButton);
	if (cButton){}

	refBuilder->get_widget<Gtk::Button>("decompress", dButton);
	if (dButton){}


	// It's not possible to delete widgets after app->run() has returned.
	// Delete the dialog with its child widgets before app->run() returns.
	pWindow->signal_hide().connect([] () { delete pWindow; });

	app->add_window(*pWindow);
	pWindow->show();
}




int main(int argc, char *argv[]) {

	// FileData<char> fd = FileReader::read_ascii_file("../tests/testfile.txt");
	// FileData<uint16_t> encoded = Encoder::encode(fd);

	// FileData<char> t = Decoder::decode(encoded);

//	auto builder = Gtk::Builder::create_from_file("ac-gui.glade", "MainWindow");
//
//	auto aButton = pWindow->get_widget<Gtk::FileChooserButton>("ASCII_input");
//	auto nButton = pWindow->get_widget<Gtk::FileChooserButton>("NULL_input");
//
//	auto compressButton = pWindow->get_widget<Gtk::Button>("compress");
//	auto decompressButton = pWindow->get_widget<Gtk::Button>("decompress");
//
//	auto oLabel = pWindow->get_widget<Gtk::Label>("output");

	app = Gtk::Application::create("org.gtkmm.example");

	// Instantiate a dialog when the application has been activated.
	// This can only be done after the application has been registered.
	// It's possible to call app->register_application() explicitly, but
	// usually it's easier to let app->run() do it for you.
	app->signal_activate().connect([] () { on_app_activate(); });

	return app->run(argc, argv);

}