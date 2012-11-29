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
        self.ui.button_keystore.clicked.connect(self.keystorePath)

        # Get the stored preferences
        self.sdkdir = self.prefs.get('sdkdir')
        self.keystore = self.prefs.get('keystore')
        self.keystorepassold = self.prefs.get('keystorepass')
        self.keyalias = self.prefs.get('keyalias')
        self.keyaliaspassold = self.prefs.get('keyaliaspass')

        # Set the UI text
        self.ui.lineSDK.setText(self.sdkdir)
        self.ui.linekeystore.setText(self.keystore)
        self.ui.linekeystorepass.setText('notyourrealpass')
        self.ui.linekeyalias.setText(self.keyalias)
        self.ui.linekeyaliaspass.setText('notyourrealpass')

        # Show the dialog
        self.show()
        self.exec_()

    # Show the SDK selector dialogs
    def SDKPath(self):
        self.sdkdir = QtGui.QFileDialog.getExistingDirectory(self, 'Choose Android SDK dir')
        self.sdkdir = str(self.sdkdir)
        # Try to determine if the user has already installed android-10 in the SDK
        if not os.path.isdir(self.sdkdir + '/platforms/android-10'):
            QtGui.QMessageBox.information(self, 'Android 2.3.3 SDK Platform not installed',
                                        'Please install the Android 2.3.3 (API 10) SDK Platform ' +
                                        'from the Android SDK manager before trying to package anything.')
        self.ui.lineSDK.setText(self.sdkdir)

    # Show the keystore selector dialogs
    def keystorePath(self):
        self.keystore = QtGui.QFileDialog.getOpenFileName(self, 'Choose Key Store file')
        self.keystore = str(self.keystore)
        # Try to determine if the user has already installed android-10 in the SDK
        if not os.path.isfile(self.keystore):
            QtGui.QMessageBox.information(self, 'Keystore file not valid',
                                        'Please choose a valid keystore.')
        self.ui.linekeystore.setText(self.keystore)

    # Save the preferences
    def accept(self):
        "Save user proposed options"
        self.keystorepass = str( self.ui.linekeystorepass.text() )
        self.keyaliaspass = str( self.ui.linekeyaliaspass.text() )
        self.keyalias     = str( self.ui.linekeyalias.text() )
        self.prefs.set('sdkdir', self.sdkdir)
        self.prefs.set('keystore', self.keystore)
        self.prefs.set('keyalias', self.keyalias)
        # Only save the password if the user has changed it
        if self.keystorepass != self.keystorepassold:
            self.prefs.set('keystorepass', self.keystorepass)
            QtGui.QMessageBox.information(self, 'Your password is being saved unsecurely!',
                                        'Please understand that your key store password has been saved unsecurely in the preferences file.')
        if self.keyaliaspass != self.keyaliaspassold:
            self.prefs.set('keyaliaspass', self.keyaliaspass)
            QtGui.QMessageBox.information(self, 'Your password is being saved unsecurely!',
                                        'Please understand that your key alias password has been saved unsecurely in the preferences file.')
        self.hide()

    # Discard preferences
    def reject(self):
        self.hide()

