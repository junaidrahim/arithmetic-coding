#include <gtkmm.h>

int main(int argc, char *argv[]) {
	auto app = Gtk::Application::create("org.pdc");

	Gtk::Window window;
	window.set_title("Arithmetic Coding");
	window.set_default_size(400,400);

	return app->run(window);
}