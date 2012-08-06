#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main packager code for the BennuGD packager.
    The interface itself is holded in ui_mainwindow.ui/py"""

import os,sys

# Import the Qt4 modules
from PyQt4 import QtCore,QtGui

# Import the compiled UI module
from ui_mainwindow import Ui_MainWindow
from dialog_preferences import dialog_preferences
from preferences import preferences

# Create a class for our main window
class packager(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        
        # This is always the same
        self.ui=Ui_MainWindow()
        self.ui.setupUi(self)
        
        # Initialize the preferences, display dialog in case SDK dir nonexistant
        self.prefs = preferences()
        self.sdkdir = self.prefs.get('sdkdir')
        if not os.path.isdir(self.sdkdir + '/platforms/android-10'):
            self.show_preferences()
        
        # Connect the signals
        self.ui.actionPreferences.triggered.connect(self.show_preferences)
        self.ui.actionQuit.triggered.connect(sys.exit)
        self.ui.button_appdirselector.clicked.connect(self.dirselector)
        self.ui.button_package.clicked.connect(self.package)
        
        # Set default values
        self.appdir = ''
        self.appdescriptor = ''

    # Show the Directory selector dialogs
    def dirselector(self):
        self.appdir = QtGui.QFileDialog.getExistingDirectory(self, 'Choose game dir')
        self.appdir = str(self.appdir)
        self.ui.line_appdir.setText(self.appdir)
        
        # TODO: We should now populate the QListView

    def center(self):
        qr = self.frameGeometry()
        cp = QtGui.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def show_preferences(self):
        # This function displays the preferences
        dialog=dialog_preferences()

    def package(self):
        # Check for android-10 SDK platform, refuse to package otherwise
        if not os.path.isdir(self.sdkdir + '/platforms/android-10'):
            QtGui.QMessageBox.critical(self, 'Android 2.3.3 SDK Platform not installed',
                                        "Please install the Android 2.3.3 (API 10) SDK Platform " +
                                        "from the Android SDK manager before trying to package anything")
            sys.stderr.write("Android 2.3.3 SDK Platform not installed, aborting packaging\n")
            return

        # Get the values from the user
        self.appos = self.ui.appOSselector.currentText()
        self.appos = str(self.appos)
        
        # Will actually have to read values from QListView, but we'll do that later
        if not os.path.isdir(self.appdir):
            QtGui.QMessageBox.critical(self, 'Game dir not readable', 'Cannot read game dir')
            return
        
        self.appdescriptor = self.ui.line_applabel.text()

        sys.stdout.write('Packaging for: %s\n' % self.appos)
        sys.stdout.write('App dir: %s\n' % self.appdir)
        sys.stdout.write('App descriptor: %s\n' % self.appdescriptor)
        # Package the user-selected app
        QtGui.QMessageBox.information(self, 'Not implemented',
                                          'Not quite there yet :(')
