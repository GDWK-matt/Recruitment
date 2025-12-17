#include "agentstvo.h"
#include "auth.h"

class Menu {
public:
	void adminMenu(Agentstvo& agency, AuthSystem& auth);//
	void userMenu(Agentstvo& agency, const std::string& username);//
};


