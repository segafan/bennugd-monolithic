# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui_mainwindow.ui'
#
# Created: Sun Aug 12 22:05:18 2012
#      by: PyQt4 UI code generator 4.9.1
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(966, 600)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.verticalLayout_2 = QtGui.QVBoxLayout()
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.label_appfiles = QtGui.QLabel(self.centralwidget)
        self.label_appfiles.setObjectName(_fromUtf8("label_appfiles"))
        self.verticalLayout_2.addWidget(self.label_appfiles)
        self.filelist = QtGui.QListWidget(self.centralwidget)
        self.filelist.setObjectName(_fromUtf8("filelist"))
        self.verticalLayout_2.addWidget(self.filelist)
        self.horizontalLayout.addLayout(self.verticalLayout_2)
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.label_appOSselector = QtGui.QLabel(self.centralwidget)
        self.label_appOSselector.setObjectName(_fromUtf8("label_appOSselector"))
        self.horizontalLayout_3.addWidget(self.label_appOSselector)
        self.appOSselector = QtGui.QComboBox(self.centralwidget)
        self.appOSselector.setEnabled(False)
        self.appOSselector.setObjectName(_fromUtf8("appOSselector"))
        self.appOSselector.addItem(_fromUtf8(""))
        self.horizontalLayout_3.addWidget(self.appOSselector)
        self.verticalLayout.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_7 = QtGui.QHBoxLayout()
        self.horizontalLayout_7.setObjectName(_fromUtf8("horizontalLayout_7"))
        self.line_appdir = QtGui.QLineEdit(self.centralwidget)
        self.line_appdir.setEnabled(False)
        self.line_appdir.setObjectName(_fromUtf8("line_appdir"))
        self.horizontalLayout_7.addWidget(self.line_appdir)
        self.button_appdirselector = QtGui.QPushButton(self.centralwidget)
        self.button_appdirselector.setObjectName(_fromUtf8("button_appdirselector"))
        self.horizontalLayout_7.addWidget(self.button_appdirselector)
        self.verticalLayout.addLayout(self.horizontalLayout_7)
        self.horizontalLayout_4 = QtGui.QHBoxLayout()
        self.horizontalLayout_4.setObjectName(_fromUtf8("horizontalLayout_4"))
        self.label_applabel = QtGui.QLabel(self.centralwidget)
        self.label_applabel.setObjectName(_fromUtf8("label_applabel"))
        self.horizontalLayout_4.addWidget(self.label_applabel)
        self.line_applabel = QtGui.QLineEdit(self.centralwidget)
        self.line_applabel.setEnabled(False)
        self.line_applabel.setReadOnly(False)
        self.line_applabel.setObjectName(_fromUtf8("line_applabel"))
        self.horizontalLayout_4.addWidget(self.line_applabel)
        self.verticalLayout.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_5 = QtGui.QHBoxLayout()
        self.horizontalLayout_5.setObjectName(_fromUtf8("horizontalLayout_5"))
        self.label_appname = QtGui.QLabel(self.centralwidget)
        self.label_appname.setObjectName(_fromUtf8("label_appname"))
        self.horizontalLayout_5.addWidget(self.label_appname)
        self.line_appname = QtGui.QLineEdit(self.centralwidget)
        self.line_appname.setObjectName(_fromUtf8("line_appname"))
        self.horizontalLayout_5.addWidget(self.line_appname)
        self.verticalLayout.addLayout(self.horizontalLayout_5)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.label_debug = QtGui.QLabel(self.centralwidget)
        self.label_debug.setObjectName(_fromUtf8("label_debug"))
        self.horizontalLayout_2.addWidget(self.label_debug)
        self.combo_debug = QtGui.QComboBox(self.centralwidget)
        self.combo_debug.setObjectName(_fromUtf8("combo_debug"))
        self.combo_debug.addItem(_fromUtf8(""))
        self.combo_debug.addItem(_fromUtf8(""))
        self.horizontalLayout_2.addWidget(self.combo_debug)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        spacerItem = QtGui.QSpacerItem(20, 40, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem)
        self.horizontalLayout_6 = QtGui.QHBoxLayout()
        self.horizontalLayout_6.setObjectName(_fromUtf8("horizontalLayout_6"))
        self.check_install = QtGui.QCheckBox(self.centralwidget)
        self.check_install.setChecked(True)
        self.check_install.setObjectName(_fromUtf8("check_install"))
        self.horizontalLayout_6.addWidget(self.check_install)
        self.button_package = QtGui.QPushButton(self.centralwidget)
        self.button_package.setObjectName(_fromUtf8("button_package"))
        self.horizontalLayout_6.addWidget(self.button_package)
        self.verticalLayout.addLayout(self.horizontalLayout_6)
        self.horizontalLayout.addLayout(self.verticalLayout)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 966, 25))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        self.menuEmulator = QtGui.QMenu(self.menubar)
        self.menuEmulator.setObjectName(_fromUtf8("menuEmulator"))
        self.menuAVD = QtGui.QMenu(self.menuEmulator)
        self.menuAVD.setObjectName(_fromUtf8("menuAVD"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.actionPreferences = QtGui.QAction(MainWindow)
        self.actionPreferences.setObjectName(_fromUtf8("actionPreferences"))
        self.actionQuit = QtGui.QAction(MainWindow)
        self.actionQuit.setObjectName(_fromUtf8("actionQuit"))
        self.actionAndroid = QtGui.QAction(MainWindow)
        self.actionAndroid.setObjectName(_fromUtf8("actionAndroid"))
        self.menuFile.addAction(self.actionPreferences)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.actionQuit)
        self.menuEmulator.addAction(self.menuAVD.menuAction())
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuEmulator.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QtGui.QApplication.translate("MainWindow", "BennuGD Packager", None, QtGui.QApplication.UnicodeUTF8))
        self.label_appfiles.setText(QtGui.QApplication.translate("MainWindow", "Detected game files:", None, QtGui.QApplication.UnicodeUTF8))
        self.filelist.setToolTip(QtGui.QApplication.translate("MainWindow", "<html><head/><body><p>The list of files that will get packed.</p><p>Please note that some files (*.exe, *.dll...) will not actually be copied.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.label_appOSselector.setText(QtGui.QApplication.translate("MainWindow", "Target OS:", None, QtGui.QApplication.UnicodeUTF8))
        self.appOSselector.setToolTip(QtGui.QApplication.translate("MainWindow", "The OS you\'re packaging your app for", None, QtGui.QApplication.UnicodeUTF8))
        self.appOSselector.setItemText(0, QtGui.QApplication.translate("MainWindow", "Android", None, QtGui.QApplication.UnicodeUTF8))
        self.line_appdir.setPlaceholderText(QtGui.QApplication.translate("MainWindow", "Please choose a dir", None, QtGui.QApplication.UnicodeUTF8))
        self.button_appdirselector.setText(QtGui.QApplication.translate("MainWindow", "Select game directory...", None, QtGui.QApplication.UnicodeUTF8))
        self.label_applabel.setText(QtGui.QApplication.translate("MainWindow", "App descriptor:", None, QtGui.QApplication.UnicodeUTF8))
        self.line_applabel.setToolTip(QtGui.QApplication.translate("MainWindow", "<html><head/><body><p>Unique ID for your app, should include your company\'s name and you game\'s name.</p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.line_applabel.setText(QtGui.QApplication.translate("MainWindow", "org.libsdl.app", None, QtGui.QApplication.UnicodeUTF8))
        self.label_appname.setText(QtGui.QApplication.translate("MainWindow", "App name:", None, QtGui.QApplication.UnicodeUTF8))
        self.line_appname.setToolTip(QtGui.QApplication.translate("MainWindow", "User-visible name for your app", None, QtGui.QApplication.UnicodeUTF8))
        self.line_appname.setPlaceholderText(QtGui.QApplication.translate("MainWindow", "Name to be shown to the user", None, QtGui.QApplication.UnicodeUTF8))
        self.label_debug.setText(QtGui.QApplication.translate("MainWindow", "Package for:", None, QtGui.QApplication.UnicodeUTF8))
        self.combo_debug.setToolTip(QtGui.QApplication.translate("MainWindow", "Choose if you want to package for debug or for release", None, QtGui.QApplication.UnicodeUTF8))
        self.combo_debug.setItemText(0, QtGui.QApplication.translate("MainWindow", "Debug", None, QtGui.QApplication.UnicodeUTF8))
        self.combo_debug.setItemText(1, QtGui.QApplication.translate("MainWindow", "Release", None, QtGui.QApplication.UnicodeUTF8))
        self.check_install.setToolTip(QtGui.QApplication.translate("MainWindow", "Install resultng APK to device or emulator", None, QtGui.QApplication.UnicodeUTF8))
        self.check_install.setText(QtGui.QApplication.translate("MainWindow", "Install APK", None, QtGui.QApplication.UnicodeUTF8))
        self.button_package.setToolTip(QtGui.QApplication.translate("MainWindow", "Click when you feel ready to package your app", None, QtGui.QApplication.UnicodeUTF8))
        self.button_package.setText(QtGui.QApplication.translate("MainWindow", "Package && Install", None, QtGui.QApplication.UnicodeUTF8))
        self.menuFile.setTitle(QtGui.QApplication.translate("MainWindow", "&File", None, QtGui.QApplication.UnicodeUTF8))
        self.menuEmulator.setTitle(QtGui.QApplication.translate("MainWindow", "&Android", None, QtGui.QApplication.UnicodeUTF8))
        self.menuAVD.setTitle(QtGui.QApplication.translate("MainWindow", "AVD", None, QtGui.QApplication.UnicodeUTF8))
        self.actionPreferences.setText(QtGui.QApplication.translate("MainWindow", "Preferences", None, QtGui.QApplication.UnicodeUTF8))
        self.actionPreferences.setToolTip(QtGui.QApplication.translate("MainWindow", "Preferences dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.actionPreferences.setShortcut(QtGui.QApplication.translate("MainWindow", "Ctrl+,", None, QtGui.QApplication.UnicodeUTF8))
        self.actionQuit.setText(QtGui.QApplication.translate("MainWindow", "Quit", None, QtGui.QApplication.UnicodeUTF8))
        self.actionQuit.setShortcut(QtGui.QApplication.translate("MainWindow", "Ctrl+Q", None, QtGui.QApplication.UnicodeUTF8))
        self.actionAndroid.setText(QtGui.QApplication.translate("MainWindow", "Android", None, QtGui.QApplication.UnicodeUTF8))

