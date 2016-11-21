#pragma once

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>

class Ui : public Gtk::Window
{
	public:
		Ui();
		virtual ~Ui();

	protected:
		// Signal handlers:
		void on_button_clicked(Glib::ustring data);
		void on_button_quit();

		// Member widgets:
		Gtk::Grid m_grid;
		Gtk::Button m_button_1, m_button_2, m_button_quit;
};
