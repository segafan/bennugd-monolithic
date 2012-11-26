#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main packager code for the BennuGD packager.
    The interface itself is holded in ui_mainwindow.ui/py"""

import os,sys,uuid,shutil,subprocess,gzip

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

        # Now, try to ensure ANT is installed
        if sys.platform.startswith('win') and not os.path.isdir( str(os.getenv('ANT_HOME')) ):
            QtGui.QMessageBox.critical(self, 'ANT not found',
                "You don't appear to have ANT correctly installed in your system, you can "+
                "install it with winant-install-v7.exe from the BennuGD Packager dir.")
            sys.exit()


        # Initialize the preferences, display dialog in case SDK dir nonexistant
        self.prefs = preferences()
        self.sdkdir = self.prefs.get('sdkdir')
        if not os.path.isdir(self.sdkdir):
            self.show_preferences()
            # Reread the user-given value, if any
            self.sdkdir = self.prefs.get('sdkdir')

        # Windows is stupid
        self.batext=''
        self.exeext=''
        if sys.platform.startswith('win'):
            self.batext='.bat'
            self.exeext='.exe'

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
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'android'+self.batext),
                              'sdk'])
            except:
                QtGui.QMessageBox.critical(self, 'SDK manager launch error',
                              'Couldn\'t launch the SDK Manager, sorry :(\n'+
                              '(Maybe you haven\'t configured the SDK path correctly?)')
        elif action == 'AVD Manager':
            try:
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'android'+self.batext),
                              'avd'])
            except:
                QtGui.QMessageBox.critical(self, 'AVD manager launch error',
                              'Couldn\'t launch the Android Virtual Device Manager, sorry :(\n'+
                              '(Maybe you haven\'t configured the SDK path correctly?)')
        elif action == 'Monitor':
            try:
                subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'monitor'+self.batext)])
            except:
                QtGui.QMessageBox.critical(self, 'Monitor launch error',
                              'Couldn\'t launch the Android Monitor, sorry :(\n'+
                            '(Maybe you haven\'t configured the SDK path correctly?)')
        else:
            sys.stdout.write('Unknown menu action\n')

    def update_icon(self):
        'Update the icons for the app'
        iconpath = QtGui.QFileDialog.getOpenFileName(self, "Choose icon file",
                                               self.appdir,
                                               "Images (*.png *.jpg *.bmp)");
        if iconpath != '':
            icon1 = QtGui.QIcon()
            icon1.addPixmap(QtGui.QPixmap(iconpath), QtGui.QIcon.Normal, QtGui.QIcon.Off)
            self.sender().setIcon(icon1)

    def list_emulators(self):
        '''Return a list with the installed emulators as reported by
           android list avd'''
        avdlist = []
        try:
            output = subprocess.check_output([os.path.join(self.sdkdir, 'tools', 'android'+self.batext),
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
            subprocess.Popen([os.path.join(self.sdkdir, 'tools', 'emulator'+self.exeext),
                                 '-avd', str( self.sender().text() )])
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

        # Populate the QListWidget
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

    def uncompresstree(self, src, exts=None):
        """Handles uncompression of gzip files with given extensions in given dir
        Taken from shutil.copytree"""
        names = os.listdir(src)

        errors = []
        for name in names:
            srcname = os.path.join(src, name)
            try:
                if os.path.isdir(srcname):
                    self.uncompresstree(srcname, exts)
                else:
                    # gzip won't raise an exception until we try to actually
                    # uncompress data
                    f_in = gzip.open(srcname, 'rb')
                    f_out = open(srcname+'.out', 'wb')
                    success = True
                    try:
                        f_out.writelines(f_in)
                    except IOError:
                        # Not in gz format
                        success = False
                    f_in.close()
                    f_out.close()

                    if success:
                        # Replace compressed file with uncompressed version
                        os.remove(srcname)
                        os.rename(srcname+'.out', srcname)
                    else:
                        os.remove(srcname+'.out')

            except (IOError, os.error) as why:
                errors.append((srcname, str(why)))
            # catch the Error from the recursive copytree so that we can
            # continue with other files
            except Error as err:
                errors.extend(err.args[0])
        if errors:
            raise Error(errors)

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

        self.appdescriptor = str( self.ui.line_applabel.text() )
        if self.appdescriptor == '':
            QtGui.QMessageBox.critical(self, 'App descriptor empty', 'The app descriptor cannot be left empty.')
            return

        self.appname = self.ui.line_appname.text()
        if self.appname == '':
            QtGui.QMessageBox.critical(self, 'App name empty', 'The app name cannot be left empty.')
            return

        # Pack for landscape or portrait
        self.apporientation = self.ui.combo_orientation.currentText()

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
            self.uncompresstree( os.path.join(workdir, 'assets'), ('.fpg', '.map', '.fnt') )

            # Change what's needed to be changed in the template
            fd = open(os.path.join(workdir, 'local.properties'), 'w')
            # We want the UNIX-like PATH
            fd.write('sdk.dir=%s\n' % self.sdkdir.replace('\\', '/'))
            fd.close()

            # Create default.properties
            fd = open(os.path.join(workdir, 'default.properties'), 'w')
            fd.write('target=android-10\n')
            fd.close()

            # Create strings.xml
            fd = open(os.path.join(workdir, 'res', 'values', 'strings.xml'), 'w')
            fd.write('<?xml version="1.0" encoding="utf-8"?>\n')
            fd.write('<resources>\n')
            fd.write('    <string name="app_name">%s</string>\n' % self.appname)
            fd.write('</resources>\n')
            fd.close()

            # Create the directory with the Java wrapper
            wrapper_path = os.path.join(workdir, 'src', self.appdescriptor.replace('.', '/'))
            wrapper_path = os.path.normpath(wrapper_path)
            print "Creating %s" % wrapper_path
            os.makedirs(wrapper_path)
            fd = open(os.path.join(wrapper_path, 'MyGame.java'), 'w')
            fd.write('package %s;\n' % self.appdescriptor)
            fd.write('import org.libsdl.app.SDLActivity;\n')
            fd.write('import android.os.*;\n')
            fd.write('public class MyGame extends SDLActivity {\n')
            fd.write('    protected void onCreate(Bundle savedInstanceState) {\n')
            fd.write('        super.onCreate(savedInstanceState);\n')
            fd.write('    }\n')
            fd.write('    protected void onDestroy() {\n')
            fd.write('        super.onDestroy();\n')
            fd.write('    }\n')
            fd.write('}\n')
            fd.close()

            # Create AndroidManifest.xml
            fd = open(os.path.join(workdir, 'AndroidManifest.xml'), 'w')
            fd.write('<?xml version="1.0" encoding="utf-8"?>\n')
            fd.write('<manifest xmlns:android="http://schemas.android.com/apk/res/android"\n')
            fd.write('      package="%s"\n' % self.appdescriptor)
            fd.write('      android:versionCode="1"\n')
            fd.write('      android:versionName="1.0">\n')
            fd.write('        <application android:label="@string/app_name" android:icon="@drawable/icon" android:theme="@android:style/Theme.NoTitleBar.Fullscreen">\n')
            fd.write('        <activity android:name="MyGame"\n')
            if self.apporientation == 'Landscape':
                fd.write('                  android:screenOrientation="sensorLandscape"\n')
            else:
                fd.write('                  android:screenOrientation="portrait"\n')
            fd.write('                  android:label="@string/app_name">\n')
            fd.write('            <intent-filter>\n')
            fd.write('                <action android:name="android.intent.action.MAIN" />\n')
            fd.write('                <category android:name="android.intent.category.LAUNCHER" />\n')
            fd.write('            </intent-filter>\n')
            fd.write('        </activity>\n')
            fd.write('    </application>\n')
            fd.write('    <uses-sdk android:minSdkVersion="9" android:targetSdkVersion="10"/>\n')
            fd.write('    <uses-feature android:glEsVersion="0x00020000" />\n')
            fd.write('    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />\n')
            fd.write('</manifest>\n')
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
                retval = subprocess.call(['ant'+self.batext, self.target, 'install'])
            else:
                retval = subprocess.call(['ant'+self.batext, self.target])

            # If the apk was generated correctly, ask the user for the output
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
                    #shutil.rmtree(workdir, True)
                else:
                    QtGui.QMessageBox.critical(self, 'Game dir not readable', 'Cannot read APK output dir.')
            else:
                QtGui.QMessageBox.critical(self, 'APK creation failed', 'APK creation failed with return code '+str(retval))

        self.ui.statusbar.clearMessage()
        # Return to the app working dir
        os.chdir(mycwd)
