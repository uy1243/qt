import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import Qt.labs.platform 1.0

ApplicationWindow {
    visible: true
    width: 240
    height: 240
    title: qsTr("show")
    color: "whitesmoke"
    id:loginw
    MenuBar {
          Menu {
              title: qsTr("&Device")
              menuItem{
                  onTriggered: console.debug("open device")
              }

          }
      }

    Item {
        id: mainShow

        anchors.fill: parent;

        Rectangle{
            anchors.fill: parent;
            color:'blue'
        }


        MouseArea{

            anchors.fill: parent;
            onClicked: { parent.color = 'red' }
        }

    }
}
