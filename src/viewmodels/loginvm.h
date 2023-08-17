#pragma once

#include <QObject>

class ViewNavigator;

class LoginVM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

public:
    explicit LoginVM(ViewNavigator* viewNavigator, QObject *parent = nullptr);

    const QString &login() const;
    void setLogin(const QString &newLogin);

    const QString &password() const;
    void setPassword(const QString &newPassword);

signals:
    void loginChanged();
    void passwordChanged();

public slots:
    void authorize();

private:
    QString m_login = "hello";
    QString m_password = "world";
    ViewNavigator* m_viewNavigator;
};

