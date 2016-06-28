import QtQuick 2.7
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TableView {
        id: mytable
        anchors.fill: parent
        width: parent.width
        sortIndicatorVisible: true

        model: MY_MODEL;

        TableViewColumn {
            role: "nu"
            title: ""
            width: 50

            movable: false
            resizable: false
            delegate: Item {
                Text {
                    text: styleData.row + 1
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        TableViewColumn {
            role: "datetime"
            title: qsTr("Issued date")
            width: 100
        }
    }

}
