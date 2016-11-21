#include "ui.hpp"
#include <iostream>


Ui::Ui()
	: m_button_1("Hello World"),
	m_button_2("Button 2"),
	m_button_quit("Quit")
{
	set_title("Hello Title!");
	set_border_width(10);

	add(m_grid);

	m_grid.add(m_button_1);
	m_grid.add(m_button_2);
	m_grid.attach_next_to(m_button_quit, m_button_1, Gtk::POS_BOTTOM, 2, 1);

	m_button_1.signal_clicked().connect(
			sigc::bind<Glib::ustring>(sigc::mem_fun(
					*this, &Ui::on_button_clicked), "button 1"));

	
	m_button_2.signal_clicked().connect(
			sigc::bind<Glib::ustring>(sigc::mem_fun(
					*this, &Ui::on_button_clicked), "button 2"));

	m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &Ui::on_button_quit));

	show_all_children();
}

Ui::~Ui()
{

}

void Ui::on_button_clicked(Glib::ustring data)
{
	std::cout << data << std::endl;
}

void Ui::on_button_quit()
{
	hide();
}
