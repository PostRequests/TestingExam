
#include <iostream>
#include "SaverUserManager.h"
#include "Option.h"
int main()
{
    system("chcp 1251>nul");
    std::string str = "Привет";
    Admin z("login", "pwd1", "fullName", "89069746951");
    Guest b("Guest", "Guest", "Guest", "89069746951");
    SaverUserManager sav(Option::pathUsers);
    sav.save(z);
    sav.save(b);
    UserManager usrs =  sav.load();
    for (auto& a : usrs.users) {
        std::cout << a->ToString() << std::endl;
    }
}

