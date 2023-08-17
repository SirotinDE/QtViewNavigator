import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.Layouts 1.1
import enumPages 1.0

Page {
    property var viewModel: viewNavigator.getViewModel(EnumPages.LOGIN, "loginPage")

    objectName: "loginPage"
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: layout.height + Theme.paddingLarge

        Column {
            id: layout
            width: parent.width

            Item {
                id: spacer
                width: parent.width
                height: parent.height * 0.5
            }

            Label {
                text: "login"
                width: parent.width
            }

            TextField {
                width: parent.width
                text: viewModel.login
            }

            Label {
                text: "password"
                width: parent.width
            }

            TextField {
                width: parent.width
                text: viewModel.password
            }

            Button {
                text: "authorize"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {

                }
            }

        }
    }
}
