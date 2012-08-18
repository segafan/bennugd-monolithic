#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main packager code for the BennuGD packager.
    The interface itself is holded in ui_mainwindow.ui/py"""

import os,sys,uuid,shutil,subprocess

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
        self.ui.iconprovider = QtGui.QFileIconProvider()
        
        # Initialize the preferences, display dialog in case SDK dir nonexistant
        self.prefs = preferences()
        self.sdkdir = self.prefs.get('sdkdir')
        if not os.path.isdir(self.sdkdir):
            self.show_preferences()
            # Reread the user-given value, if any
            self.sdkdir = self.prefs.get('sdkdir')
        
        # Connect the signals
        self.ui.actionPreferences.triggered.connect(self.show_preferences)
        self.ui.actionQuit.triggered.connect(sys.exit)
        self.ui.actionSDK_Manager.triggered.connect(self.menuitem)
        self.ui.actionAVD_Manager.triggered.connect(self.menuitem)
        self.ui.actionDDMS.triggered.connect(self.menuitem)
        self.ui.button_appdirselector.clicked.connect(self.dirselector)
        self.ui.button_package.clicked.connect(self.package)
        self.ui.check_install.stateChanged.connect(self.check_install_changed)
        self.ui.icon_hdpi.clicked.connect(self.update_icon)
        self.ui.icon_mdpi.clicked.connect(self.update_icon)
        self.ui.icon_ldpi.clicked.connect(self.update_icon)
        
        # Set default values
        self.appdir = ''
        self.appdescriptor = ''
        
        # Get the list of installed AVDs
        avdlist = self.list_emulators()
        for avd in avdlist:
            action = QtGui.QAction(self)
            action.setObjectName(avd)
            action.setText(avd)
            action.triggered.connect(self.launch_emulator)
            self.ui.menuAVD.addAction(action)
    
    def menuitem(self):
        'Takes care of handling miscellaneous menu item actions'
        action = self.sender().text()
        
        if action == 'SDK Manager':
            try:
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'android'),
                              'sdk'])
            except:
                QtGui.QMessageBox.critical(self, 'SDK manager launch error',
                              'Couldn\'t launch the SDK Manager, sorry :(\n'+
                              '(Maybe you haven\'t configured the SDK path correctly?)')
        elif action == 'AVD Manager':
            try:
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'android'),
                              'avd'])
            except:
                QtGui.QMessageBox.critical(self, 'AVD manager launch error',
                              'Couldn\'t launch the Android Virtual Device Manager, sorry :(\n'+
                              '(Maybe you haven\'t configured the SDK path correctly?)')
        elif action == 'DDMS':
            try:
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'ddms')])
            except:
                QtGui.QMessageBox.critical(self, 'DDMS launch error',
                              'Couldn\'t launch the Dalvik Debug Monitor Server (DDMS), sorry :(\n'+
                            '(Maybe you haven\'t configured the SDK path correctly?)')
        else:
            sys.stdout.write('Unknown menu action\n')
                
    def update_icon(self):
        'Update the icons for the app'
        iconpath = QtGui.QFileDialog.getOpenFileName(self, "Choose icon file",
                                               self.appdir,
                                               "Images (*.png *.jpg *.bmp *.svg)");
        if iconpath != '':
            icon1 = QtGui.QIcon()
            icon1.addPixmap(QtGui.QPixmap(iconpath), QtGui.QIcon.Normal, QtGui.QIcon.Off)
            self.sender().setIcon(icon1)
    
    def list_emulators(self):
        '''Return a list with the installed emulators as reported by
           android list avd'''
        avdlist = []
        try:
            output = subprocess.check_output([os.path.join(self.sdkdir, 'tools', 'android'),
                                          'list', 'avd'], universal_newlines=True)

            for line in output.split('\n'):
                fields = line.split()
                if len(fields)>0 and fields[0] == 'Name:':
                    avdlist.append(fields[1])
        except:
                sys.stdout.write("Couldn't list available AVDs\n")

        return avdlist
    
    def launch_emulator(self):
        'Launch an emulator instance'
        try:
            subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'emulator'),
                                 '-avd', self.sender().text()])
        except:
            QtGui.QMessageBox.critical(self, 'Android emulator launch error',
                            "Couldn't open emulator instance for %s\n" % self.sender().text())
    
    # Change the "Package & Install" button text
    def check_install_changed(self):
        if self.ui.check_install.isChecked():
            self.ui.button_package.setText('Package && Install')
        else:
            self.ui.button_package.setText('Package')

    def dirselector(self):
        'Show the Directory selector dialogs'
        self.appdir = QtGui.QFileDialog.getExistingDirectory(self, 'Choose game dir', self.appdir)
        self.appdir = str(self.appdir)
        self.ui.line_appdir.setText(self.appdir)
        
        # TODO: We should now populate the QListWidget
        self.ui.filelist.clear()
        row=0
        for root, dirs, files in os.walk(self.appdir):
            if '.svn' in dirs:
                dirs.remove('.svn')

            for file in files:
                fpath = os.path.join(root, file)
                fname = fpath[(len(self.appdir)+1):]
                newItem = QtGui.QListWidgetItem()
                newIcon = self.ui.iconprovider.icon(QtCore.QFileInfo(fpath))
                newItem.setText(fname)
                newItem.setIcon(newIcon)
                self.ui.filelist.insertItem(row, newItem)
                row += 1

    def center(self):
        qr = self.frameGeometry()
        cp = QtGui.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def show_preferences(self):
        'Displays the preferences dialog'
        dialog=dialog_preferences()

    def package(self):
        'Takes care of packaging the given app'
        # Check for android-10 SDK platform, refuse to package otherwise
        if not os.path.isdir(self.sdkdir + '/platforms/android-10'):
            QtGui.QMessageBox.critical(self, 'Android 2.3.3 SDK Platform not installed',
                                        'Please install the Android 2.3.3 (API 10) SDK Platform ' +
                                        'from the Android SDK manager before trying to package anything')
            return
        
        # Save the CWD
        mycwd = os.getcwd()

        # Get the values from the user
        self.appos = self.ui.appOSselector.currentText()
        self.appos = str(self.appos)
        self.appinstall = self.ui.check_install.isChecked()
        
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
        
        # Pack for debug or release
        self.apptarget = self.ui.combo_debug.currentText()
        if self.apptarget == 'Debug':
            self.target = 'debug'
        else:
            self.target = 'release'
        
        # Create the workdir
        if sys.platform.startswith('win'):
            workdir = os.path.join(os.getenv('TMP'), 'bgdp_'+str( uuid.uuid1()))
        elif sys.platform == 'darwin':
            workdir = os.path.join('/private', 'tmp', 'bgdp_'+str( uuid.uuid1()))
        else:
            workdir = os.path.join('/tmp', 'bgdp_'+str( uuid.uuid1()))

        # Print some debug info
        sys.stdout.write('Packaging for: %s\n' % self.appos)
        sys.stdout.write('Workdir: %s\n' % workdir)
        
        # Copy the template to the workdir
        if self.appos == 'Android':
            self.ui.statusbar.showMessage('Packaging...')
            tpldir = os.path.join(mycwd, 'templates', 'android')
        
            # Copy the template to the workdir and the game into the template
            pattern = shutil.ignore_patterns('.svn', '.hg*', '*.exe', '*.dll', 
                        '*.bat', '*.dylib', '*.sh')
            shutil.copytree(tpldir, workdir, ignore=pattern)
            shutil.copytree(self.appdir, os.path.join(workdir, 'assets'), ignore=pattern)
            
            # Change what's needed to be changed in the template
            fd = open(os.path.join(workdir, 'local.properties'), 'w')
            fd.write('sdk.dir=%s\n' % self.sdkdir)
            fd.close()
            
            fd = open(os.path.join(workdir, 'default.properties'), 'w')
            fd.write('target=android-10s\n' % self.sdkdir)
            fd.close()
            
            fd = open(os.path.join(workdir, 'res', 'values', 'strings.xml'), 'w')
            fd.write('<?xml version="1.0" encoding="utf-8"?>\n')
            fd.write('<resources>\n')
            fd.write('    <string name="app_name">%s</string>\n' % self.appname)
            fd.write('</resources>\n')
            fd.close()
            
            self.ui.icon_hdpi.icon().pixmap(72, 72).save(
                        os.path.join(workdir, 'res', 'drawable-hdpi', 'icon.png'))
            self.ui.icon_mdpi.icon().pixmap(48, 48).save(
                        os.path.join(workdir, 'res', 'drawable-mdpi', 'icon.png'))
            self.ui.icon_ldpi.icon().pixmap(32, 32).save(
                        os.path.join(workdir, 'res', 'drawable-ldpi', 'icon.png'))
                
            # Tell ant to package the app and, optionally, install it
            os.chdir(workdir)
            if self.appinstall:
                retval = subprocess.call(['ant', self.target, 'install'])
            else:
                retval = subprocess.call(['ant', self.target])
            
            # If the apk was generated correctly, asdk the user for the output
            # location
            if retval == 0:
                bindir = os.path.join(workdir, 'bin')
                if os.path.exists(bindir):
                    for root, dirs, files in os.walk(bindir):
                        for file in files:
                            fpath = os.path.join(root, file)
                            # Choose the aligned APK
                            if fpath.endswith('.apk') and not 'unaligned' in fpath:
                                outputdir = QtGui.QFileDialog.getSaveFileName(self, 'Savedir for APK', self.appdir)
                                outputdir = str(outputdir)
                                # The user didn't press 'Cancel'
                                if os.path.exists(os.path.dirname(outputdir)):
                                    shutil.copy(fpath, outputdir)
                    
                    # Remove workdir
                    shutil.rmtree(workdir, True)
                else:
                    QtGui.QMessageBox.critical(self, 'Game dir not readable', 'Cannot read APK output dir.')
            else:
                QtGui.QMessageBox.critical(self, 'APK creation failed', 'APK creation failed with return code '+str(retval))
        
        self.ui.statusbar.clearMessage()
        # Return to the app working dir
        os.chdir(mycwd)
