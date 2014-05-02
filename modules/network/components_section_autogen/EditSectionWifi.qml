// This file is automatically generated, please don't edit manully.
import QtQuick 2.1
import Deepin.Widgets 1.0
import "../components"

BaseEditSection {
    id: sectionWifi
    section: "wifi"
    
    header.sourceComponent: EditDownArrowHeader{
        text: dsTr("Wi-Fi")
    }

    content.sourceComponent: Column { 
        EditLineTextInput {
            id: lineSsid
            key: "ssid"
            text: dsTr("SSID")
        }
        EditLineComboBox {
            id: lineMode
            key: "mode"
            text: dsTr("Mode")
        }
        EditLineComboBox {
            id: lineBand
            key: "band"
            text: dsTr("Band")
            alwaysUpdate: true
        }
        EditLineComboBox {
            id: lineChannel
            key: "channel"
            text: dsTr("Channel")
            alwaysUpdate: true
        }
        EditLineEditComboBox {
            id: lineMacAddress
            key: "mac-address"
            text: dsTr("Device MAC Addr")
        }
        EditLineTextInput {
            id: lineClonedMacAddress
            key: "cloned-mac-address"
            text: dsTr("Cloned MAC Addr")
        }
        EditLineSwitchButton {
            id: lineVkEnableMtu
            key: "vk-enable-mtu"
            text: dsTr("Custom MTU")
        }
        EditLineSpinner {
            id: lineMtu
            key: "mtu"
            text: dsTr("MTU")
        }
    }
}
