/*
   Simple_window.cpp
   Minimally revised for C++11 features of GCC 4.6.3 or later
   Walter C. Daugherity		June 10, 2012
*/

//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
#include "Simple_window_AS.h"
#include "get_image.h"
#include "pic_index.h"
#include "search_tag.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

Vector_ref<Tagged_image> images; 
vector<int> search_images;
search_tag st;
int current_index = 0;
int upload_num = 0;
int si_nav = 0;

//------------------------------------------------------------------------------

Text logo {Point{x_max()/5+60,50}, "Aggie Snap"};
Text file_error1 {Point{390,200}, "File type not supported."};
Text file_error2 {Point{430,250}, "Please try again."};
Text url_error1 {Point{390,200}, "Please name your URL."};
Text file_good {Point{390,200}, "File upload: Successful"};

Text family_true {Point{200,600},"Family"};
Text friends_true {Point{300,700},"Friends"};
Text aggieland_true {Point{400,600},"Aggieland"};
Text pets_true {Point{500,700},"Pets"};
Text vacation_true {Point{600,600},"Vacation"};

Image pic_logo(Point(175,75), "tree.gif");

//------------------------------------------------------------------------------

Simple_window::Simple_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	home_button(Point(x_max() - 80, 0), 80, 30, "Main Menu", cb_home),		//get to main menu
    close_button(Point(x_max()/2 - 75, y_max()/2 + 225), 150, 75, "Exit Program", cb_close),   //button to exit
	file_but(Point(x_max()/2 + 50, y_max()/2 + 100), 200, 100, "Upload a File", cb_upload),  //go to upload page
	
	up_fn{Point(x_max()/4,y_max()/2 - 20),x_max()/2, 40, "File Name:"},                //in_box
    up_url{Point(x_max()/4,y_max()/2 + 50),x_max()/2, 40, "URL:"},                        //in_box
    url_name{Point(x_max()/4,y_max()/2 + 120),x_max()/2, 40, "URL File Name:"},
	upload1{Point(3*x_max()/4+10, y_max()/2 - 20), 80, 40, "upload File",cb_getimage},  //button
    upload2{Point(3*x_max()/4+10, y_max()/2 + 85), 80, 40, "upload URL",cb_geturl},  //button

	
	brow_but(Point(x_max()/2 - 250, y_max()/2 + 100), 200, 100, "Browse Library", cb_library),   //go to current library
	next_page(Point(x_max() - 100, y_max()/4), 100, y_max()/2, "Next\nPage", cb_next_page),
	prev_page(Point(0, y_max()/4),100,y_max()/2, "Previous\nPage", cb_prev_page),
	go_button(Point(x_max()/2+50,y_max()/2 - 50), 200, 200, "GO", cb_go),
	cancel_search_button(Point(x_max()/2 - 250, y_max()/2 - 50), 200, 200, "Cancel Search", cb_cancel_search),
	search_pics(Point(3*x_max()/4 + 40, y_max()/2 + 310), 150, 40, "Search by Tag", cb_search_pics),

	family{Point(150,3*x_max()/4), 100, 50, "Family", cb_tag_family},
    friends{Point(300,3*x_max()/4), 100, 50, "Friends", cb_tag_friends},
	aggieland{Point(450,3*x_max()/4), 100, 50, "Aggieland", cb_tag_aggieland},
	pets{Point(600,3*x_max()/4), 100, 50, "Pets", cb_tag_pets},
	vacation{Point(750,3*x_max()/4), 100, 50, "Vacation", cb_tag_vacation},

	
   	button_pushed(false),
	from_lib(false),
	from_upload(false),
	from_upload_fail(false),
	from_search(false),
	from_home(true),
	from_go(false),
	upload_good(false),
	url_fail(false),
	search_pressed(false),
	actual_search(false),
	file_fail(false)

{
	attach(pic_logo);
	logo.set_font_size(50);
	attach(logo);
	attach(close_button);
	attach(file_but);
	attach(brow_but);
	ofstream myfile("pic_index.txt");
	myfile << "";
	myfile.close();	
	get_image(images, "rev.jpg");
	images[0].family_val(true);
	images[0].friends_val(true);
	images[0].aggieland_val(true);
	images[0].pets_val(true);
	images[0].vacation_val(true);
	/*ofstream ofs{"pic_index.txt", ios::app}; 
 			tags t; 
 			ofs << t; 
 			ofs.close();	 
 			++upload_num;*/
	family_true.set_font_size(32);
	friends_true.set_font_size(32);
	aggieland_true.set_font_size(32);
	pets_true.set_font_size(32);
	vacation_true.set_font_size(32);
	// cout << "First screen" << endl;
}


//------------------------------------------------------------------------------

bool Simple_window::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

//------------------------------------------------------------------------------

void Simple_window::cb_home(Address, Address pw)
{  
    reference_to<Simple_window>(pw).home();    
}

void Simple_window::cb_close(Address, Address pw)
{
	reference_to<Simple_window>(pw).close();
}

void Simple_window::cb_upload(Address, Address pw)
{  
    reference_to<Simple_window>(pw).upload();    
}

void Simple_window::cb_library(Address, Address pw)
{
	reference_to<Simple_window>(pw).library();
}

void Simple_window::cb_next_page(Address, Address pw)
{
	reference_to<Simple_window>(pw).next();
}

void Simple_window::cb_prev_page(Address, Address pw)
{
	reference_to<Simple_window>(pw).prev();
}

void Simple_window::cb_getimage(Address, Address pw)
{
	reference_to<Simple_window>(pw).getimage();
}

void Simple_window::cb_geturl(Address, Address pw)
{
	reference_to<Simple_window>(pw).geturl();
}

void Simple_window::cb_go(Address, Address pw)
{
	reference_to<Simple_window>(pw).go();
}

void Simple_window::cb_cancel_search(Address, Address pw)
{
	reference_to<Simple_window>(pw).cancel_search();
}

void Simple_window::cb_tag_family(Address, Address pw)
{  
    reference_to<Simple_window>(pw).family_tag();    
}

void Simple_window::cb_tag_friends(Address, Address pw)
{  
    reference_to<Simple_window>(pw).friends_tag();    
}

void Simple_window::cb_tag_aggieland(Address, Address pw)
{  
    reference_to<Simple_window>(pw).aggieland_tag();    
}

void Simple_window::cb_tag_pets(Address, Address pw)
{  
    reference_to<Simple_window>(pw).pets_tag();    
}

void Simple_window::cb_tag_vacation(Address, Address pw)
{  
    reference_to<Simple_window>(pw).vacation_tag();    
}

void Simple_window::cb_search_pics(Address, Address pw) 
{ 
	reference_to<Simple_window>(pw).search(); 
} 
		
//------------------------------------------------------------------------------

void Simple_window::home()
{   
	button_pushed = true;
	from_home = true;
	logo.set_font_size(50);
 
    
	if(from_lib)
	{
		//detach(taglist);
        detach(next_page);
        detach(prev_page);
        detach(home_button);
		detach(search_pics); 
		detach(images[current_index]);
		if(images[current_index].family_check()) detach(family_true);
		if(images[current_index].friends_check()) detach(friends_true);
		if(images[current_index].aggieland_check()) detach(aggieland_true);
		if(images[current_index].pets_check()) detach(pets_true);
		if(images[current_index].vacation_check()) detach(vacation_true);
		current_index = 0;
        from_lib = false;
    }
     
	if(from_search)
	{
		detach(go_button);
		detach(cancel_search_button);
		detach(family);
		detach(friends);
		detach(aggieland);
		detach(pets);
		detach(vacation);
		if(actual_search)
			detach(images[search_images[si_nav]]);
		from_search = false;
		actual_search = false;
		search_pressed = false;
		st.family_val(false);
		st.friends_val(false);
		st.aggieland_val(false);
		st.pets_val(false);
		st.vacation_val(false);
		
	}
	
    if(from_upload)
    {
		if(from_upload_fail)
		{
			detach(file_error1);
			detach(file_error2);
			from_upload_fail = false;
		}
		if(upload_good)	
		{
		detach(file_good);	
		detach(family);
		detach(friends);
		detach(aggieland);
		detach(pets);
		detach(vacation);
		
		ofstream ofs{"pic_index.txt", ios::app}; 
 			tags t; 
 			ofs << t; 
 			ofs.close();	 
 			++upload_num;
		}
		
        detach(up_fn);
        detach(up_url);
		detach(url_name);
        detach(upload1);
        detach(upload2);
        detach(home_button);
        from_upload = false;
    }
		attach(pic_logo);
        attach(logo);
        attach(file_but);
        attach(brow_but);
        attach(close_button);
        Fl::redraw();
        wait_for_button();
}


void Simple_window::close()
{
	button_pushed = true;
	exit(0);
	hide();
}

void Simple_window::upload()
{
    button_pushed = true;
	from_home = false;
	from_upload = true;
        
	detach(pic_logo);
	detach(logo);
	detach(file_but);
	detach(brow_but);
	detach(close_button);
	attach(home_button);
	attach(up_fn);
	attach(up_url);
	attach(url_name);
	attach(upload1);
	attach(upload2);
	
	Fl::redraw();
	wait_for_button();
}

void Simple_window::library()
{
	// cout << "in library" << endl;
	button_pushed = true;
	from_lib = true;
	
	if(from_home)
	{
	detach(pic_logo);
	detach(logo);
	detach(file_but);
	detach(brow_but);
	detach(close_button);
	}
	
	if(from_search)
	{
	// cout << "from search; st.family_val = " << st.family_check() << endl;
	detach(go_button);
	detach(cancel_search_button);
	detach(family);
	detach(friends);
	detach(aggieland);
	detach(pets);
	detach(vacation);
	}
	
	attach(search_pics); 
	attach(home_button);
	attach(next_page);
	attach(prev_page);
	attach(images[current_index]);
	
	if(images[current_index].family_check()) attach(family_true);
	if(images[current_index].friends_check()) attach(friends_true);
	if(images[current_index].aggieland_check()) attach(aggieland_true);
	if(images[current_index].pets_check()) attach(pets_true);
	if(images[current_index].vacation_check()) attach(vacation_true);
	
	if(from_go)
	{
		// cout << "from_go is true here, in library" << endl;
		detach(images[current_index]);
		if(images[current_index].family_check()) detach(family_true);
		if(images[current_index].friends_check()) detach(friends_true);
		if(images[current_index].aggieland_check()) detach(aggieland_true);
		if(images[current_index].pets_check()) detach(pets_true);
		if(images[current_index].vacation_check()) detach(vacation_true);
		attach(images[search_images[si_nav]]);
		if(images[search_images[si_nav]].family_check()) attach(family_true);
		if(images[search_images[si_nav]].friends_check()) attach(friends_true);
		if(images[search_images[si_nav]].aggieland_check()) attach(aggieland_true);
		if(images[search_images[si_nav]].pets_check()) attach(pets_true);
		if(images[search_images[si_nav]].vacation_check()) attach(vacation_true);
		from_go = false;
	}
	
    string file_name = "pic_index.txt";        
	ofstream ofs{file_name, ios::app};
	tags t;
	ofs << t;
    ofs.close();
	
	Fl::redraw();
	wait_for_button();
}

void Simple_window::next()
{
	// cout << "in next button; search_pressed = " << search_pressed << endl;
	button_pushed = true;
	if(search_pressed)
	{
		 cout << "in search_pressed part of next()" << endl;
		 cout << "si_nav before function = " << si_nav << endl;
		 cout << "images.size() = " << images.size() << endl;
		 cout << "search_image.size() = " << search_images.size() << endl;
		 cout << "before, search_images[si_nav] = " << search_images[si_nav] << endl;
		if(search_images[si_nav] < images.size() - 1 && search_images[si_nav] < search_images.size() -1)
		{
		detach(images[search_images[si_nav]]);
		if(images[search_images[si_nav]].family_check()) detach(family_true);
		if(images[search_images[si_nav]].friends_check()) detach(friends_true);
		if(images[search_images[si_nav]].aggieland_check()) detach(aggieland_true);
		if(images[search_images[si_nav]].pets_check()) detach(pets_true);
		if(images[search_images[si_nav]].vacation_check()) detach(vacation_true);
		++si_nav;
		attach(images[search_images[si_nav]]);
		if(images[search_images[si_nav]].family_check()) attach(family_true);
		if(images[search_images[si_nav]].friends_check()) attach(friends_true);
		if(images[search_images[si_nav]].aggieland_check()) attach(aggieland_true);
		if(images[search_images[si_nav]].pets_check()) attach(pets_true);
		if(images[search_images[si_nav]].vacation_check()) attach(vacation_true);
		 cout << "si_nav after function is " << si_nav << endl;
		 cout << "after, search_images[si_nav] is " << search_images[si_nav] << endl;
		}
		else;
	}
	else
	{
		if(current_index < (images.size() - 1))
		{
		detach(images[current_index]);
		if(images[current_index].family_check()) detach(family_true);
		if(images[current_index].friends_check()) detach(friends_true);
		if(images[current_index].aggieland_check()) detach(aggieland_true);
		if(images[current_index].pets_check()) detach(pets_true);
		if(images[current_index].vacation_check()) detach(vacation_true);
		++current_index;
		attach(images[current_index]);
		if(images[current_index].family_check()) attach(family_true);
		if(images[current_index].friends_check()) attach(friends_true);
		if(images[current_index].aggieland_check()) attach(aggieland_true);
		if(images[current_index].pets_check()) attach(pets_true);
		if(images[current_index].vacation_check()) attach(vacation_true);
		}
	}
	Fl::redraw();
	wait_for_button();
}

void Simple_window::prev()
{
	button_pushed = true;
	
	if(search_pressed)
	{
		if(search_images[si_nav] > 0)
		{
		detach(images[search_images[si_nav]]);
		if(images[search_images[si_nav]].family_check()) detach(family_true);
		if(images[search_images[si_nav]].friends_check()) detach(friends_true);
		if(images[search_images[si_nav]].aggieland_check()) detach(aggieland_true);
		if(images[search_images[si_nav]].pets_check()) detach(pets_true);
		if(images[search_images[si_nav]].vacation_check()) detach(vacation_true);
		--si_nav;
		attach(images[search_images[si_nav]]);
		if(images[search_images[si_nav]].family_check()) attach(family_true);
		if(images[search_images[si_nav]].friends_check()) attach(friends_true);
		if(images[search_images[si_nav]].aggieland_check()) attach(aggieland_true);
		if(images[search_images[si_nav]].pets_check()) attach(pets_true);
		if(images[search_images[si_nav]].vacation_check()) attach(vacation_true);
		}
	}
	else
	{
		if(current_index > 0)
		{
		detach(images[current_index]);
		if(images[current_index].family_check()) detach(family_true);
		if(images[current_index].friends_check()) detach(friends_true);
		if(images[current_index].aggieland_check()) detach(aggieland_true);
		if(images[current_index].pets_check()) detach(pets_true);
		if(images[current_index].vacation_check()) detach(vacation_true);
		//detach(taglist);
		--current_index;
		attach(images[current_index]);
		if(images[current_index].family_check()) attach(family_true);
		if(images[current_index].friends_check()) attach(friends_true);
		if(images[current_index].aggieland_check()) attach(aggieland_true);
		if(images[current_index].pets_check()) attach(pets_true);
		if(images[current_index].vacation_check()) attach(vacation_true);
		}
	}
	Fl::redraw();
	wait_for_button();
}

void Simple_window::getimage()
{
	string file_name = up_fn.get_string();
	
	while(file_name == "\0")
	{
		if(url_fail)
		{
			url_fail = false;
			detach(url_error1);
		}
		file_fail = true;
		attach(file_error1);
		attach(file_error2);
		file_name = up_fn.get_string();
		Fl::redraw();
		wait_for_button();
	}
	while(check(file_name))
	{
		if(url_fail)
		{
			url_fail = false;
			detach(url_error1);
		}
		file_fail = true;
		attach(file_error1);
		attach(file_error2);
		file_name = up_fn.get_string();
		Fl::redraw();
		wait_for_button();
	}
	upload_good = true;
	detach(file_error1);
	detach(file_error2);
	file_good.set_font_size(32);
	attach(file_good);
	Fl::redraw();
	get_image(images,file_name);
	tag_image();

}



bool Simple_window::check(string file_name)
{
	if((file_name[file_name.size ()- 1] == 'g' && file_name[file_name.size() - 2] == 'e' && file_name[file_name.size() - 3] == 'p' && file_name[file_name.size() - 4] == 'j' && file_name[file_name.size() - 5] == '.')
		|| (file_name[file_name.size() - 1] == 'g' && file_name[file_name.size() - 2] == 'p' && file_name[file_name.size() - 3] == 'j' && file_name[file_name.size() - 4] == '.')
		|| (file_name[file_name.size() - 1] == 'f' && file_name[file_name.size() - 2] == 'i' && file_name[file_name.size() - 3] == 'g' && file_name[file_name.size() - 4] == '.'))
		from_upload_fail = false;
	else if((file_name[file_name.size ()- 1] == 'G' && file_name[file_name.size() - 2] == 'E' && file_name[file_name.size() - 3] == 'P' && file_name[file_name.size() - 4] == 'J' && file_name[file_name.size() - 5] == '.'))
		{
			file_name[file_name.size()-1]='g';
			file_name[file_name.size()-2]='e';
			file_name[file_name.size()-3]='p';
			file_name[file_name.size()-4]='j';
			from_upload_fail=false;
		}
	else if((file_name[file_name.size ()- 1] == 'G' && file_name[file_name.size() - 2] == 'P' && file_name[file_name.size() - 3] == 'J' && file_name[file_name.size() - 4] == '.'))
		{
			file_name[file_name.size()-1]='g';
			file_name[file_name.size()-2]='p';
			file_name[file_name.size()-3]='j';
			from_upload_fail=false;
		}	
	else if((file_name[file_name.size ()- 1] == 'F' && file_name[file_name.size() - 2] == 'I' && file_name[file_name.size() - 3] == 'G' && file_name[file_name.size() - 4] == '.'))
		{
			file_name[file_name.size()-1]='f';
			file_name[file_name.size()-2]='i';
			file_name[file_name.size()-3]='g';
			from_upload_fail=false;
		}

	else {
	from_upload_fail = true;
	file_error1.set_font_size(32);
	file_error2.set_font_size(32);
	
}
return from_upload_fail;
}



void Simple_window::geturl()
{
	string file_name = url_name.get_string();
	string named_url = up_url.get_string();
	
	while(named_url == "\0")
	{
		if(file_fail)
		{
			file_fail = false;
			detach(file_error1);
			detach(file_error2);
		}
		url_fail = true;
		attach(url_error1);
		named_url = up_url.get_string();
		Fl::redraw();
		wait_for_button();
	}
	while(check(named_url))
	{
		attach(url_error1);
		named_url = up_url.get_string();
		Fl::redraw();
		wait_for_button();
	}
	upload_good = true;
	detach(url_error1);
	file_good.set_font_size(32);
	attach(file_good);
	Fl::redraw();
	get_url(images,file_name,named_url);
	tag_image();
	
}


void Simple_window::tag_image()
{
	// cout << "in tag image; search_pressed = " << search_pressed << endl;
	if (search_pressed) {
		// cout << "searchpressed = 1 in tag image " << endl;
		detach(images[current_index]);
		detach(next_page);
		detach(prev_page);
		if(images[current_index].family_check()) detach(family_true);
		if(images[current_index].friends_check()) detach(friends_true);
		if(images[current_index].aggieland_check()) detach(aggieland_true);
		if(images[current_index].pets_check()) detach(pets_true);
		if(images[current_index].vacation_check()) detach(vacation_true);
		detach(search_pics);
		detach(home_button);
		attach(family);
		attach(friends);
		attach(aggieland);
		attach(pets);
		attach(vacation);
		attach(go_button);
		attach(cancel_search_button);
		}
	else {
		detach(up_fn);
		detach(up_url);
		detach(url_name);
		detach(upload1);
		detach(upload2);
		attach(family);
		attach(friends);
		attach(aggieland);
		attach(pets);
		attach(vacation);
		from_upload = true;
		}
		// cout << st.family_check() << " " << st.friends_check() << " " << st.aggieland_check();
	// cout << " " << st.pets_check() << " " << st.vacation_check() << endl;
	Fl::redraw();
	wait_for_button();
}

void Simple_window::search()		//FIX
{
	button_pushed = true;
	search_pressed = true;
	from_search = true;
	// cout << "in the search function, press = true" << endl;
	st.family_val(false);
	st.friends_val(false);
	st.aggieland_val(false);
	st.pets_val(false);
	st.vacation_val(false);
	search_images.clear();
	// cout << "just cleared search_images vector; size = " << search_images.size() << endl;
	// cout << st.family_check() << " " << st.friends_check() << " " << st.aggieland_check();
	// cout << " " << st.pets_check() << " " << st.vacation_check() << endl;
	tag_image();
	}

void Simple_window:: go() 
{
	from_go = true;
	actual_search = true;
	// cout << "in Go; st.family_val = " << st.family_check() << endl;
	current_index = 0;
	si_nav = 0;
	
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == false)
		{
		from_go = false;
		library();
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == false)
		{
		for(auto i = 0; i<images.size(); ++i)
		{
			// cout << " the size of search_images is " << search_images.size() << endl;
			if(images[i].family_check() == true)
			{
				search_images.push_back(i);
				// cout << " the size of search_images is " << search_images.size() << endl;
			}
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == false)
		{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == false)
		{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].aggieland_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == false)
		{
		for(auto i = 0; i<images.size(); ++i)
			if(images[i].pets_check() == true)
				search_images.push_back(i);
		}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == true)
		{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
// one under this is 6
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == false)
		{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].aggieland_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].pets_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].vacation_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].aggieland_check())
				search_images.push_back(i);
		}
	}
// above 11
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].pets_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].vacation_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].pets_check() == true && images[i].aggieland_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].pets_check() == true && images[i].vacation_check())
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].aggieland_check() == true && images[i].vacation_check())
				search_images.push_back(i);
		}
	}
// above 16
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true && images[i].aggieland_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].aggieland_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].pets_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
// above 21
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].aggieland_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].aggieland_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].vacation_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].friends_check() == true && images[i].aggieland_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].aggieland_check() == true && images[i].pets_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
//above 26
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == false)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true 
			&& images[i].aggieland_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == false 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true 
			&& images[i].vacation_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == false && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true 
			&& images[i].aggieland_check() == true && images[i].vacation_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == true && st.friends_check() == false && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].vacation_check() == true 
			&& images[i].aggieland_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
	if(st.family_check() == false && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].vacation_check() == true && images[i].friends_check() == true 
			&& images[i].aggieland_check() == true && images[i].pets_check() == true)
				search_images.push_back(i);
		}
	}
// above 31
	if(st.family_check() == true && st.friends_check() == true && st.aggieland_check() == true 
		&& st.pets_check() == true && st.vacation_check() == true)
				{
		for(auto i = 0; i<images.size(); ++i)
		{
			if(images[i].family_check() == true && images[i].friends_check() == true 
			&& images[i].aggieland_check() == true && images[i].pets_check() == true
			&& images[i].aggieland_check() == true)
				search_images.push_back(i);
		}
	}	
	
	library();
}

void Simple_window::cancel_search()
{
	search_pressed = false;
	actual_search = false;
	home();
	Fl::redraw();
	wait_for_button();
}

void Simple_window::family_tag()
{
	// cout << "in family_tag; search_pressed = " << search_pressed << endl;
	if(search_pressed) {
		// cout << "st.family_val changes to one" << endl;
		st.family_val(true); 
		}
	else {
		// cout << "family_tag, not using search " << endl;
		images[images.size() - 1].family_val(true);
		}
	wait_for_button();
}

void Simple_window::friends_tag()
{
	if(search_pressed)
		st.friends_val(true);
	else
		images[images.size() - 1].friends_val(true);
	wait_for_button();
}

void Simple_window::aggieland_tag()
{
	if(search_pressed)
		st.aggieland_val(true);
	else
	images[images.size() - 1].aggieland_val(true);
	wait_for_button();
}

void Simple_window::pets_tag()
{
	if(search_pressed)
		st.pets_val(true);
	else
		images[images.size() - 1].pets_val(true);
	wait_for_button();
}

void Simple_window::vacation_tag()
{
	if(search_pressed)
		st.vacation_val(true);
	else
		images[images.size() - 1].vacation_val(true);
	wait_for_button();
}

//------------------------------------------------------------------------------



