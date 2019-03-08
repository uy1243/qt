import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import Qt.labs.platform 1.0

ApplicationWindow {
    visible: true
    width: 600
    height: 500
    title: qsTr("show")
    color: "whitesmoke"
    id:loginw
    MenuBar {
        Menu {
            title: qsTr("&Device")
            menuItem{
                text: "open device"
                onTriggered: console.debug("open device")
            }

        }
    }

    Item {
        id: mainShow
        width:300
        height:400

        x:24
        y:0


        Rectangle{
            Grid{
                anchors.fill: parent;
                columns: 10
                rows: 10
                spacing: 1
            }

            anchors.fill: parent;
            //color:'black'
            MouseArea{
               anchors.fill: parent;
                onClicked: {
                    parent.color = 'red'
                    mw.showMessInGUI('red');
                }
            }
        }

    }
}
