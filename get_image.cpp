#include "get_image.h"

namespace Graph_lib {

void get_image(Vector_ref<Tagged_image>& v, string file_name) { // put image in vector_ref
	v.push_back(new Tagged_image (Point(150,150),file_name));	
	}
	
//--------------------------------------------------------------------------------------------------------------------------------------------------

void get_url(Vector_ref<Tagged_image>& v, string file_name, string url) { // put image from URL into vector_ref
	system((string("wget ")+ url + " -O " + file_name).c_str());
	v.push_back(new Tagged_image (Point(150,150),file_name));
	}
	
	}