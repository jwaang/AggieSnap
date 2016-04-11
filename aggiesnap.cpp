#include "Simple_window_AS.h"
#include "Graph_proj.h"
#include "std_lib_facilities_4.h"

int main(){
	try{
		using namespace Graph_lib;
	
		Simple_window win(Point(0, 0), 1000, 800, "Aggie Snaps");
		
		win.wait_for_button();
		return 0;
	}
	catch(exception& e){
		cerr << "exception: " << e.what() << '\n';
			return 1;
	}
	catch(...){
		cerr << "Some exception\n";
		return 2;
	}
}
//------------------------------------------------------------------------------------------------------------------

