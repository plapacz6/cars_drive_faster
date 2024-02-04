#include <iostream>
#include "T_CLI.h"

using namespace std;
namespace csfgame {

T_CLI::T_CLI(TUserLanguage lang)
    : lang{lang}
{
    message[TUserLanguage::ENG][TCLIMessages::basic_control] =
        "esc      - end\n<-  ->   - control car";

    message[TUserLanguage::PL][TCLIMessages::basic_control] =
        "esc      - koniec\n<-  ->   - sterowanie samochodem";
}

//T_CLI::~T_CLI() override { }

//setters and getters:
//void T_CLI::set_(TTT) { }
//TTT T_CLI::get_() const { }

void T_CLI::print_message(TCLIMessages msg) {
    cout << message[lang][msg] << endl;
}

} //namespace csfgame
