/*
 * Copyright (c) 2021, Aleksei Belkin <mailbelkin@gmail.com>.
 * All rights reserved.
*/
import QtQuick 2.11
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: qsTr("Streebog calc hash")
    Connections {
            target: appCore
            function onSendToQml(hashSum) {
                hashSumText.text = hashSum
            }
            function onBusyChanged(flag) {
                btnOpenFile.enabled=!flag;
                btnCalculate.enabled=!flag;
                btncopy.enabled=!flag;
                rb256.enabled=!flag;
                rb512.enabled=!flag;
                fileNameTextField.enabled=!flag;
                hashSumText.enabled=!flag;
                chkBox.enabled=!flag;
            }
        }
   BusyIndicator {
        id: busyId
        anchors.centerIn: parent
        running: appCore.busy
    }
    FileDialog{
        id: openFileDialog
        title:  qsTr("Choose file")
        folder: shortcuts.home
        selectExisting: true
        nameFilters: ["All files (*.*)"]
        onAccepted: {
            fileNameTextField.text = fileUrl
        }
        onRejected: {
            fileNameTextField.clear()
        }
    }
   GroupBox{
       title: qsTr("Hash function algoritm GOST 34.11-2012")
       anchors.fill: parent
        Column{
            anchors.fill: parent
            Button{
                id:btnOpenFile
                width: parent.width
                text:qsTr("Open File")
                onClicked: {
                    openFileDialog.open();
                }
            }
            TextField {
                id: fileNameTextField
                width: parent.width
            }
            Row{
                RadioButton{
                    id:rb256
                    text: "256"
                    onClicked: {
                        appCore.rb256Checked();
                    }
                }
                RadioButton{
                    id:rb512
                    checked: true
                    text: "512"
                    onClicked: {
                        appCore.rb512Checked();
                    }
                }
            }
            Button{
                id:btnCalculate
                width: parent.width
                text:qsTr("Calculate")
                onClicked: {
                    hashSumText.clear()
                    appCore.calculateHash(fileNameTextField.text)
                    hashSumText.cursorPosition =0
                }
            }
            CheckBox{
                id:chkBox
                text:qsTr("big-endian")
                onClicked: {
                    hashSumText.clear()
                    appCore.receiveCheckBoxState(checkState)
                }
            }
            TextField {
                id: hashSumText
                selectByMouse: true
                width: parent.width
            }
            Button{
                id:btncopy
                width: parent.width
                text:qsTr("Copy")
                onClicked: {
                    hashSumText.selectAll()
                    hashSumText.copy()
                }
            }
        }
   }
}
