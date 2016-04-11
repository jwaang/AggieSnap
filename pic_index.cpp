#include "pic_index.h"
#include "Simple_window_AS.h"

istream& operator>>(istream& is, tags& t){
        char ch1 = 0;
        tags tt;
        if(is >> tt.filename >> ch1 
                  >> tt.family >> tt.friends >> tt.aggieland >> tt.pets >> tt.vacation){
                if(ch1!=':'){
                        is.clear(ios_base::failbit);
                        return is;
                }
        }
        else return is;
        t = tt;
        return is;
}

ostream& operator<<(ostream& os, tags& t){
    bool family{false}, friends{false}, aggieland{false}, pets{false}, vacation{false};
              
	if(images[upload_num].family_check()) family=true;
	if(images[upload_num].friends_check()) friends=true;
	if(images[upload_num].aggieland_check()) aggieland=true;
	if(images[upload_num].pets_check()) pets=true;
	if(images[upload_num].vacation_check()) vacation=true;
				
    return os << images[upload_num].file_name() << " : "
                          << family << ' '
                                  << friends << ' '
                                  << aggieland << ' '
                                  << pets << ' '
                                  << vacation << '\n';
}
