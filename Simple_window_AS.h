//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph_proj.h"
#include "get_image.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

extern Vector_ref<Tagged_image> images;
extern int current_index;
extern int upload_num;

//------------------------------------------------------------------------------

struct Simple_window : Graph_lib::Window {
    Simple_window(Point xy, int w, int h, const string& title );
    bool wait_for_button(); // simple event loop
private:
	String URLstring, filename_string;
    Button home_button;		//all - main menu
	Button close_button;	//main menu
	Button file_but;		//main menu
	Button brow_but;		//main menu
	Button upload1;			//upload page
	Button upload2;			//upload page
	//Out_box taglist;        //upload page
	Button search_pics; 
	In_box up_fn;			//upload page
	In_box up_url;			//upload page
	In_box url_name;		//upload page
	Button next_page;		//library page
	Button prev_page;		//library page
	Button go_button;
	Button cancel_search_button;
	Button family;
	Button friends;
	Button aggieland;
	Button pets;
	Button vacation;

	bool button_pushed;     // implementation detail
	bool from_lib;
	bool from_upload;
	bool from_upload_fail;
	bool upload_good;
	bool url_fail;
	bool file_fail;
	bool search_pressed;
	bool from_search;
	bool from_home;
	bool from_go;
	bool actual_search;


	static void cb_home(Address, Address);
	static void cb_dir_up(Address, Address);
	static void cb_url_up(Address, Address);
	static void cb_upload(Address, Address);
	static void cb_library(Address, Address);
	static void cb_close(Address, Address);
	static void cb_next_page(Address, Address);
	static void cb_prev_page(Address, Address);
	static void cb_getimage(Address, Address);
	static void cb_geturl(Address, Address);
	static void cb_search_pics(Address, Address);
	static void cb_go(Address, Address);
	static void cb_cancel_search(Address, Address);
	static void cb_tag_family(Address, Address);
	static void cb_tag_friends(Address, Address);
	static void cb_tag_aggieland(Address, Address);
	static void cb_tag_pets(Address, Address);
	static void cb_tag_vacation(Address, Address);
	static void cb_tag_image(Address, Address);

	
    void home();
	void upload();
	void library();
	void close();
	void next();
	void prev();
	void getimage();
	void geturl();
	bool check(string file_name);
	void tag_image();
	void search();
	void go();
	void cancel_search();
	void family_tag();
	void friends_tag();
	void aggieland_tag();
	void pets_tag();
	void vacation_tag();

	

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD

//-----------------------------------------------------------------------------------------------
//end of file


