#ifndef T_CLI_H
#define T_CLI_H

#include <map>
#include <string>
#include <iostream>

namespace csfgame {

enum class TUserLanguage {
    ENG = 0, PL = 1
};
enum class TCLIMessages {
    basic_control
};

class T_CLI {
public:

    T_CLI(TUserLanguage lang);
    T_CLI(const  T_CLI&) = delete;
    virtual ~T_CLI() = default;
    T_CLI& operator=(const T_CLI&) = delete;

    //setters and getters:
    //void set_(TTT);
    //TTT get_() const;
    TUserLanguage lang;
    std::map<TUserLanguage, std::map<TCLIMessages, std::string>> message;

    void print_message(TCLIMessages msg);

protected:
private:
};


} //namespace csfgame
#endif //T_CLI_H
