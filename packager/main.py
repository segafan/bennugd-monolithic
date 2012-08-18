#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main program file for BennuGD packager"""

import os,sys

# Import Qt modules
from PyQt4 import QtCore,QtGui

# Other dialogs
from packager import packager

def main():
    # Set the CWD to the directory containing main.py
    # This is needed when launching from a graphic shell
    mypwd = os.path.realpath(__file__)
    os.chdir(os.path.dirname(mypwd))

    app = QtGui.QApplication(sys.argv)
    window=packager()

    # Center the window
    window.center()
    window.show()

    # It's exec_ because exec is a reserved word in Python
    sys.exit(app.exec_())
    

if __name__ == "__main__":
    main()

