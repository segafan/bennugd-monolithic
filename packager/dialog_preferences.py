#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria     

"""This is the preferences dialog file for the BennuGD packager.
It relies in the UI file (created automagically by pyuic4
from the QT Designer project file)"""

import os,sys
from PyQt4 import QtCore, QtGui
from ui_preferences import Ui_Preferences
from preferences import preferences

# A class for managing the credits window
class dialog_preferences(QtGui.QDialog):
    def __init__(self):
        QtGui.QDialog.__init__(self)
        
        # Initialize preferences
        self.prefs = preferences()
        
        # This is always the same
        self.ui=Ui_Preferences()
        self.ui.setupUi(self)
        self.ui.button_SDKPath.clicked.connect(self.SDKPath)
        
        # Now set the line text to the preference value
        self.ui.lineSDK.setText(self.prefs.get('sdkdir'))
        self.sdkdir = self.prefs.get('sdkdir')
        
        # Show the dialog
        self.show()
        self.exec_()
    
    # Show the Directory selector dialogs
    def SDKPath(self):
        self.sdkdir = QtGui.QFileDialog.getExistingDirectory(self, 'Choose Android SDK dir')
        self.sdkdir = str(self.sdkdir)
        # Try to determine if the user has already installed android-10 in the SDK
        if not os.path.isdir(self.sdkdir + '/platforms/android-10'):
            QtGui.QMessageBox.information(self, 'Android 2.3.3 SDK Platform not installed',
                                        'Please install the Android 2.3.3 (API 10) SDK Platform ' +
                                        'from the Android SDK manager before trying to package anything.<br />'+
                                        '<a href="http://developer.android.com/sdk/index.html">Installation instructions</a>')
        self.ui.lineSDK.setText(self.sdkdir)

    # Save the preferences
    def accept(self):
        "Save user proposed SDK dir"
        self.prefs.set('sdkdir', self.sdkdir)
        self.hide()
    
    # Discard preferences
    def reject(self):
        self.hide()

