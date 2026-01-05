import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 300
    height: 200
    visible: true
    title: "Phase-1"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            //counter 从外部引入
            text: "Count: " + counter.value
            font.pixelSize: 24
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
                onClicked: counter.increment()
            }
        }
    }
}
