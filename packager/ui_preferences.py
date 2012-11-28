# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui_preferences.ui'
#
# Created: Wed Nov 28 13:20:56 2012
#      by: PyQt4 UI code generator 4.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_Preferences(object):
    def setupUi(self, Preferences):
        Preferences.setObjectName(_fromUtf8("Preferences"))
        Preferences.resize(475, 153)
        self.layoutWidget = QtGui.QWidget(Preferences)
        self.layoutWidget.setGeometry(QtCore.QRect(10, 10, 451, 134))
        self.layoutWidget.setObjectName(_fromUtf8("layoutWidget"))
        self.verticalLayout = QtGui.QVBoxLayout(self.layoutWidget)
        self.verticalLayout.setMargin(0)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.horizontalLayout_5 = QtGui.QHBoxLayout()
        self.horizontalLayout_5.setObjectName(_fromUtf8("horizontalLayout_5"))
        self.labelSDK = QtGui.QLabel(self.layoutWidget)
        self.labelSDK.setObjectName(_fromUtf8("labelSDK"))
        self.horizontalLayout_5.addWidget(self.labelSDK)
        self.lineSDK = QtGui.QLineEdit(self.layoutWidget)
        self.lineSDK.setEnabled(False)
        self.lineSDK.setObjectName(_fromUtf8("lineSDK"))
        self.horizontalLayout_5.addWidget(self.lineSDK)
        self.button_SDKPath = QtGui.QPushButton(self.layoutWidget)
        self.button_SDKPath.setObjectName(_fromUtf8("button_SDKPath"))
        self.horizontalLayout_5.addWidget(self.button_SDKPath)
        self.verticalLayout.addLayout(self.horizontalLayout_5)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.labelkeystore = QtGui.QLabel(self.layoutWidget)
        self.labelkeystore.setObjectName(_fromUtf8("labelkeystore"))
        self.horizontalLayout.addWidget(self.labelkeystore)
        self.linekeystore = QtGui.QLineEdit(self.layoutWidget)
        self.linekeystore.setEnabled(False)
        self.linekeystore.setStatusTip(_fromUtf8(""))
        self.linekeystore.setObjectName(_fromUtf8("linekeystore"))
        self.horizontalLayout.addWidget(self.linekeystore)
        self.button_keystore = QtGui.QPushButton(self.layoutWidget)
        self.button_keystore.setObjectName(_fromUtf8("button_keystore"))
        self.horizontalLayout.addWidget(self.button_keystore)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.labelkeystorepass = QtGui.QLabel(self.layoutWidget)
        self.labelkeystorepass.setObjectName(_fromUtf8("labelkeystorepass"))
        self.horizontalLayout_3.addWidget(self.labelkeystorepass)
        self.linekeystorepass = QtGui.QLineEdit(self.layoutWidget)
        self.linekeystorepass.setEchoMode(QtGui.QLineEdit.Password)
        self.linekeystorepass.setObjectName(_fromUtf8("linekeystorepass"))
        self.horizontalLayout_3.addWidget(self.linekeystorepass)
        self.verticalLayout.addLayout(self.horizontalLayout_3)
        self.buttonBox = QtGui.QDialogButtonBox(self.layoutWidget)
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.verticalLayout.addWidget(self.buttonBox)

        self.retranslateUi(Preferences)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), Preferences.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), Preferences.reject)
        QtCore.QMetaObject.connectSlotsByName(Preferences)

    def retranslateUi(self, Preferences):
        Preferences.setWindowTitle(QtGui.QApplication.translate("Preferences", "Preferences", None, QtGui.QApplication.UnicodeUTF8))
        self.labelSDK.setText(QtGui.QApplication.translate("Preferences", "Android SDK dir:", None, QtGui.QApplication.UnicodeUTF8))
        self.lineSDK.setPlaceholderText(QtGui.QApplication.translate("Preferences", "Please choose path to SDK", None, QtGui.QApplication.UnicodeUTF8))
        self.button_SDKPath.setText(QtGui.QApplication.translate("Preferences", "Choose...", None, QtGui.QApplication.UnicodeUTF8))
        self.labelkeystore.setText(QtGui.QApplication.translate("Preferences", "KeyStore:", None, QtGui.QApplication.UnicodeUTF8))
        self.linekeystore.setPlaceholderText(QtGui.QApplication.translate("Preferences", "[Optional] Please choose path to Android Keystore", None, QtGui.QApplication.UnicodeUTF8))
        self.button_keystore.setText(QtGui.QApplication.translate("Preferences", "Choose...", None, QtGui.QApplication.UnicodeUTF8))
        self.labelkeystorepass.setText(QtGui.QApplication.translate("Preferences", "KeyStore password:", None, QtGui.QApplication.UnicodeUTF8))

