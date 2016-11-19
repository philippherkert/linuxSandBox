#pragma once

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Ui : public Gtk::Window
{
	public:
		Ui();
		virtual ~Ui();

	protected:
		// Signal handlers:
		void on_button_clicked();

		// Member widgets:
		Gtk::Button m_button;
};
