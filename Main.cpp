
#include <iostream>
#include "SaverUserManager.h"
#include "SaveTest.h"
#include "TestManager.h"
#include "Option.h"
int main()
{
    system("chcp 1251>nul");
    /*Admin z("login", "pwd1", "fullName", "89069746951");
    Guest b("Guest", "Guest", "Guest", "89069746951");
    SaverUserManager sav(Option::pathUsers);
    sav.save(z);
    sav.save(b);
    UserManager usrs =  sav.load();
    for (auto& a : usrs.users) {
        std::cout << a->ToString() << std::endl;
    }*/
    SaveTest savTest(Option::pathTests);
    Test test("Мир");
    // Вопрос 1: Столица России
    Question q1;
    q1.setQuestionText("Столица России");
    q1.addAnswer("Москва", true)
        .addAnswer("Красноярск", false)
        .addAnswer("Санкт-Петербург", false)
        .addAnswer("Новосибирск", false);
    test.addQuestion(q1);
    
  
    TestManager m =  savTest.load();
    auto te = m.getTest("Мир");
    std::cout << te->size() << std::endl;
    std::cout << te->getScore(4) << std::endl;
    for (auto l : m.getListNameTest()) {
        std::cout << l << std::endl;
    }
}

