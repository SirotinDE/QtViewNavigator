#include "loginvm.h"

LoginVM::LoginVM(ViewNavigator* viewNavigator,
                 QObject *parent)
    : QObject(parent)
    , m_viewNavigator(viewNavigator)
{

}

const QString &LoginVM::login() const
{
    return m_login;
}

void LoginVM::setLogin(const QString &newLogin)
{
    if (m_login == newLogin)
        return;
    m_login = newLogin;
    emit loginChanged();
}

const QString &LoginVM::password() const
{
    return m_password;
}

void LoginVM::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

void LoginVM::authorize(){

}
