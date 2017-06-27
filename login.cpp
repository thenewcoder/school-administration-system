#include "login.h"

bool Login::validLogin(const QString &username, const QString &password)
{
    // TODO: write proper login check later
    if (username == "Test" && password == "1234")
        return true;
    return false;
}
