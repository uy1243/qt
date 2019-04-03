import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import Qt.labs.platform 1.0

ApplicationWindow {
    visible: true
    width: 600
    height: 500
    title: qsTr("show")
    color: 	"#708090"
    id:loginw
    MenuBar {
        Menu {
            title: qsTr("&Device")
            menuItem{
                text: "open device"
                onTriggered: {
                   console.error("err!")

                }
            }
        }
    }

    ToolBar {
        id: toolBar
        x: 0
        y: 0
        width: parent.width
        height: 40

        ToolButton {
            id: toolButton
            x: 12
            y: 2
            text: qsTr("Config")
            onClicked: {
                var component = Qt.createComponent("vec.qml")
                console.log("ready!")
                if (component.status==Component.Ready) {
                    component.createObject(loginw,{"x": 100, "y": 100})
                    //dialog.sqlPosition = positionRoot
                }
            }
        }
        Rectangle {
            id: rectangle
            x: 0
            y: 40
            width: parent.width
            height: parent.height-80
            color: "#000000"
            Text {
                id: name
               // text: qsTr(mw.CANMess);
            }

            Button{

                width:80
                height: 80
                onClicked: mw.showMess("config failed!");
            }
        }
    }
}
