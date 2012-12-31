# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui_mainwindow.ui'
#
# Created: Mon Dec 31 02:13:24 2012
#      by: PyQt4 UI code generator 4.9.6
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName(_fromUtf8("MainWindow"))
        MainWindow.resize(740, 567)
        self.centralwidget = QtGui.QWidget(MainWindow)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.horizontalLayout_4 = QtGui.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_4.setObjectName(_fromUtf8("horizontalLayout_4"))
        self.verticalLayout = QtGui.QVBoxLayout()
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.graphicsView = QtGui.QGraphicsView(self.centralwidget)
        self.graphicsView.setMouseTracking(False)
        self.graphicsView.setObjectName(_fromUtf8("graphicsView"))
        self.verticalLayout.addWidget(self.graphicsView)
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.zoomlevel = QtGui.QSpinBox(self.centralwidget)
        self.zoomlevel.setMinimum(1)
        self.zoomlevel.setMaximum(10000)
        self.zoomlevel.setProperty("value", 100)
        self.zoomlevel.setObjectName(_fromUtf8("zoomlevel"))
        self.horizontalLayout_2.addWidget(self.zoomlevel)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_4.addLayout(self.verticalLayout)
        self.verticalLayout_2 = QtGui.QVBoxLayout()
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        self.table = QtGui.QTableWidget(self.centralwidget)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.table.sizePolicy().hasHeightForWidth())
        self.table.setSizePolicy(sizePolicy)
        self.table.setMinimumSize(QtCore.QSize(200, 0))
        self.table.setMaximumSize(QtCore.QSize(200, 16777215))
        self.table.setObjectName(_fromUtf8("table"))
        self.table.setColumnCount(2)
        self.table.setRowCount(0)
        item = QtGui.QTableWidgetItem()
        item.setText(_fromUtf8("X"))
        self.table.setHorizontalHeaderItem(0, item)
        item = QtGui.QTableWidgetItem()
        item.setText(_fromUtf8("Y"))
        self.table.setHorizontalHeaderItem(1, item)
        self.table.horizontalHeader().setDefaultSectionSize(63)
        self.verticalLayout_2.addWidget(self.table)
        self.horizontalLayout_3 = QtGui.QHBoxLayout()
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.button_addcenter = QtGui.QPushButton(self.centralwidget)
        self.button_addcenter.setObjectName(_fromUtf8("button_addcenter"))
        self.horizontalLayout_3.addWidget(self.button_addcenter)
        self.button_add = QtGui.QPushButton(self.centralwidget)
        self.button_add.setText(_fromUtf8(""))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8("res/add.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.button_add.setIcon(icon)
        self.button_add.setObjectName(_fromUtf8("button_add"))
        self.horizontalLayout_3.addWidget(self.button_add)
        self.button_del = QtGui.QPushButton(self.centralwidget)
        self.button_del.setText(_fromUtf8(""))
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(_fromUtf8("res/remove.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.button_del.setIcon(icon1)
        self.button_del.setObjectName(_fromUtf8("button_del"))
        self.horizontalLayout_3.addWidget(self.button_del)
        self.verticalLayout_2.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_4.addLayout(self.verticalLayout_2)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 740, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(MainWindow)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        MainWindow.setStatusBar(self.statusbar)
        self.action_Open = QtGui.QAction(MainWindow)
        self.action_Open.setObjectName(_fromUtf8("action_Open"))
        self.action_Save = QtGui.QAction(MainWindow)
        self.action_Save.setObjectName(_fromUtf8("action_Save"))
        self.action_Quit = QtGui.QAction(MainWindow)
        self.action_Quit.setObjectName(_fromUtf8("action_Quit"))
        self.menuFile.addAction(self.action_Open)
        self.menuFile.addAction(self.action_Save)
        self.menuFile.addSeparator()
        self.menuFile.addAction(self.action_Quit)
        self.menubar.addAction(self.menuFile.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(_translate("MainWindow", "Control Point Setter", None))
        self.button_addcenter.setToolTip(_translate("MainWindow", "Add graphic center as control point", None))
        self.button_addcenter.setText(_translate("MainWindow", "Add Center", None))
        self.button_add.setToolTip(_translate("MainWindow", "Add new control point", None))
        self.button_del.setToolTip(_translate("MainWindow", "Remove control point", None))
        self.menuFile.setTitle(_translate("MainWindow", "&File", None))
        self.action_Open.setText(_translate("MainWindow", "&Open", None))
        self.action_Open.setShortcut(_translate("MainWindow", "Ctrl+O", None))
        self.action_Save.setText(_translate("MainWindow", "&Save", None))
        self.action_Save.setShortcut(_translate("MainWindow", "Ctrl+S", None))
        self.action_Quit.setText(_translate("MainWindow", "&Quit", None))
        self.action_Quit.setShortcut(_translate("MainWindow", "Ctrl+Q", None))

