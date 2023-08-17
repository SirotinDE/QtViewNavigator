#include <auroraapp.h>
#include <QtQuick>
#include <QScopedPointer>
#include "viewnavigator.h"
#include "enums/enum_pages.h"
#include "viewmodels/loginvm.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("QtViewNavigator"));

    QScopedPointer<ViewNavigator> viewNavigator(new ViewNavigator);

    viewNavigator->setViewModel(Pages::EnPages::LOGIN,
                                {
                                    [&](){ return new LoginVM(viewNavigator.data());}
                                });

    qmlRegisterType<Pages>("enumPages", 1, 0, "EnumPages");
    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("viewNavigator", viewNavigator.data());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/QtViewNavigator.qml")));
    view->show();

    return application->exec();
}
