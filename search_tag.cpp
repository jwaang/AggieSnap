#include "search_tag.h"

namespace Graph_lib {

/* Functions to check and return tag bool values */

bool search_tag::family_check() {return family;}

bool search_tag::friends_check() {return friends;}

bool search_tag::aggieland_check() {return aggieland;}

bool search_tag::pets_check() {return pets;}

bool search_tag::vacation_check() {return vacation;}

//------------------------------------------------------------

void search_tag::family_val(bool family_in) {family = family_in;}

void search_tag::friends_val(bool friends_in) {friends = friends_in;}

void search_tag::aggieland_val(bool aggieland_in) {aggieland = aggieland_in;}

void search_tag::pets_val(bool pets_in) {pets = pets_in;}

void search_tag::vacation_val(bool vacation_in) {vacation = vacation_in;}

}