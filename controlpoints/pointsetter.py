#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria

"""This is the main code for the BennuGD control point setter.
    The interface itself is holded in ui_mainwindow.ui/py"""

import os,sys

# Import the Qt4 modules
from PyQt4 import QtCore,QtGui

# Import the compiled UI module
from ui_mainwindow import Ui_MainWindow

# Create a class for our main window
class pointsetter(QtGui.QMainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)

        # This is always the same
        self.ui=Ui_MainWindow()
        self.ui.setupUi(self)
        
        # Connect the dots
        self.ui.action_Open.triggered.connect(self.openimg)
        self.ui.action_Save.triggered.connect(self.saveimg)
        self.ui.action_Quit.triggered.connect(sys.exit)
        self.ui.zoomlevel.valueChanged.connect(self.zoom)
        self.ui.button_addcenter.clicked.connect(self.add_center)
        self.ui.button_add.clicked.connect(self.add_row)
        self.ui.button_del.clicked.connect(self.del_row)
        
        # Determine some runtime data
        if sys.platform.startswith('win'):
            self.homepath = os.getenv('USERPROFILE')
        else:
            self.homepath = os.getenv('HOME')
        self.savedir = self.homepath
        self.points = 0
        
        # Display open dialog
        self.openimg()
    
    # Add the center of the current image as control point
    def add_center(self):
        x = self.ui.graphicsView.items()[0].pixmap().width()/2.
        y = self.ui.graphicsView.items()[0].pixmap().height()/2.
        self.add_row(None, x, y)
    
    def add_row(self, ignore, x=-1, y=-1):
        self.ui.table.setRowCount(self.points+1)
        if x < 0.:
            x = 0.
        item = QtGui.QTableWidgetItem( str(x) )
        self.ui.table.setItem(self.points, 0, item)
        if y < 0.:
            y = 0.
        item = QtGui.QTableWidgetItem( str(y) )
        self.ui.table.setItem(self.points, 1, item)
        self.points += 1
    
    def del_row(self):
        row = self.ui.table.currentRow()
        if row > -1:
            self.ui.table.removeRow(row)
            self.ui.table.setRowCount(self.points-1)
            self.points -= 1
    
    def update_row(self, event):
        row = self.ui.table.currentRow()
        if row > -1:
            item = self.ui.table.item(row, 0)
            item.setText( str(event.scenePos().x()) )
            item = self.ui.table.item(row, 1)
            item.setText( str(event.scenePos().y()) )
        
    def openimg(self):
        imgpath = QtGui.QFileDialog.getOpenFileName(self, "Choose image file",
                                               self.homepath,
                                               "Images (*.bmp *.gif *.jpg *.png *.tiff *.xpm)");
        if os.path.isfile(imgpath):
            scene = QtGui.QGraphicsScene()
            pic   = QtGui.QPixmap(imgpath)
            item  = QtGui.QGraphicsPixmapItem(pic)
            item.setAcceptHoverEvents(True)
            scene.addItem(item)
            self.ui.graphicsView.setScene(scene)
            item.mousePressEvent = self.update_row
            item.hoverMoveEvent = self.mousemove
            self.zoomlevel = 1.
            if self.points:
                self.ui.table.clearContents()
            self.points = 0
    
    def saveimg(self):
        outputfname = QtGui.QFileDialog.getSaveFileName(self, 'Save PNG as...', self.savedir, "PNG Image (*.png)")
        # Convert QPixmap to QImage
        img = self.ui.graphicsView.items()[0].pixmap().toImage()
        # Set the text for the image
        n = self.ui.table.rowCount()
        for i in range(n):
            x = str( self.ui.table.item(i, 0).text() )
            y = str( self.ui.table.item(i, 1).text() )
            img.setText("BennuGD_CP%d" % i, "%s,%s" % (x, y))
        if not img.save(outputfname):
            QtGui.QMessageBox.critical(self, 'Cannot write there', 'Cannot write image to given path')
    
    def mousemove(self, event):
        self.ui.statusbar.showMessage( "X: %.0f Y: %.0f" % (event.scenePos().x(), event.scenePos().y() ) )
    
    def zoom(self):
        newzoom = self.ui.zoomlevel.value()/(100.*self.zoomlevel)
        self.ui.graphicsView.scale(newzoom, newzoom)
        self.zoomlevel = self.ui.zoomlevel.value()/100.
    
    def center(self):
        qr = self.frameGeometry()
        cp = QtGui.QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
