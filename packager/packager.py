#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main packager code for the BennuGD packager.
    The interface itself is holded in ui_mainwindow.ui/py"""

import os,sys,uuid,shutil

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
        
        # Save the CWD
        mycwd = os.getcwd()

        # Get the values from the user
        self.appos = self.ui.appOSselector.currentText()
        self.appos = str(self.appos)
        
        # Will actually have to read values from QListView, but we'll do that later
        if not os.path.isdir(self.appdir):
            QtGui.QMessageBox.critical(self, 'Game dir not readable', 'Cannot read game dir.')
            return
        
        self.appdescriptor = self.ui.line_applabel.text()
        if self.appdescriptor == '':
            QtGui.QMessageBox.critical(self, 'App descriptor empty', 'The app descriptor cannot be left empty.')
            return
        
        self.appname = self.ui.line_appname.text()
        if self.appname == '':
            QtGui.QMessageBox.critical(self, 'App name empty', 'The app name cannot be left empty.')
            return
        
        # Create the workdir
        workdir = os.path.join(os.getenv('TMP'), 'bgdp_'+str( uuid.uuid1()))

        # Print some debug info
        sys.stdout.write('Packaging for: %s\n' % self.appos)
        sys.stdout.write('Workdir: %s\n' % workdir)
        
        # Copy the template to the workdir
        if self.appos == 'Android':
            tpldir = os.path.join(mycwd, 'templates', 'android')
        
            # Copy the template to the workdir and the game into the template
            pattern = shutil.ignore_patterns('.svn', '.hg*')
            shutil.copytree(tpldir, workdir, ignore=pattern)
            shutil.copytree(self.appdir, os.path.join(workdir, 'assets'), ignore=pattern)
            
            # Change what's needed to be changed in the template
            fd = open(os.path.join(workdir, 'local.properties'), 'w')
            fd.write('sdk.dir=%s\n' % self.sdkdir)
            fd.close()
            
            fd = open(os.path.join(workdir, 'res', 'values', 'strings.xml'), 'w')
            fd.write('<?xml version="1.0" encoding="utf-8"?>\n')
            fd.write('<resources>\n')
            fd.write('    <string name="app_name">%s</string>\n' % self.appname)
            fd.write('</resources>\n')
            fd.close()
                
            # Tell ant to package the app
            os.chdir(workdir)
            os.system("ant debug")
        
        # Return to the app working dir
        os.chdir(mycwd)
