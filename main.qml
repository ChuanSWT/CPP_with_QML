import QtQuick 2.15
import QtQuick.Window 2.15
import App 1.0


Window {
    width: 300
    height: 200
    visible: true
    title: "Phase-1"
    Backend{
        id:backend
    }
    Column {
        anchors.centerIn: parent
        spacing: 20
        Row{
            spacing:20
            Text {
                text: "Count: " + backend.value
                font.pixelSize: 24
            }
            Text {
                text: "Count: " + backend.multi_thread_value
                font.pixelSize: 24
            }
        }


        Rectangle {
            width: 120
            height: 40
            radius: 6
            color: "#3498db"

            Text {
                anchors.centerIn: parent
                text: "Add"
                color: "white"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    backend.increment()
                    backend.multiThreadValueIncrement()
                }
            }
        }
    }
}
