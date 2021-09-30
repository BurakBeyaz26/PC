import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.15

ApplicationWindow {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("PC")
    color: "white"


    Connections
    {
        target: __datamanage
        onColorChanged:
        {
            root.color = colorName
        }
    }

}
