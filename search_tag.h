#include "Graph_proj.h"
#include "Simple_window_AS.h"

namespace Graph_lib {
	
	struct search_tag{
		
		bool family_check();
		bool friends_check();
		bool aggieland_check();
		bool pets_check();
		bool vacation_check();
		
		void family_val(bool family_in);
		void friends_val(bool friends_in);
		void aggieland_val(bool aggieland_in);
		void pets_val(bool pets_in);
		void vacation_val(bool vacation_in);
		
	private:
		bool family{false}, friends{false}, aggieland{false}, pets{false}, vacation{false};
	};

}