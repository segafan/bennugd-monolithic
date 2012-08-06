#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2012 Joseba García Etxebarria     

"""This file includes a class for managing preferences.
The preferences are managed in a per-user basis and are stored
in each user's private dir as a SQLite DB."""

import os, sys, sqlite3

class preferences():
    # Check whether the prefs file already exists and initialize it
    # otherwise
    def __init__(self):
        sdkdir = ''
        if sys.platform.startswith('win'):
            self.dbpath = os.getenv('APPDATA')+'/BennuGD_packager/prefs.sqlite'
        elif sys.platform == 'darwin':
            self.dbpath = os.getenv('HOME')+'/Library/Application Support/BennuGD_packager/prefs.sqlite'
        else:
            self.dbpath = os.getenv('HOME')+'/.config/bennugd_packager/prefs.sqlite'
        
        # If the file already exists, refuse to try to intialize it
        if os.path.isfile(self.dbpath):
            return
        
        if not os.path.isdir(os.path.dirname(self.dbpath)):
            # We should always be able to write to our own directory...
            try:
                os.makedirs(os.path.dirname(self.dbpath))
            except OSError:
                sys.stderr.write("Couldn't initialize %s, sorry\n" % self.dbpath)
                return
        
        # Debug
        print self.dbpath+" doesn't exists, creating it"
        
        # DB doesn't exist => initialize it
        try:
            conn = sqlite3.connect(self.dbpath)
        except OperationalError:
            sys.stderr.write("Couldn't initialize %s, sorry\n" % self.dbpath)
            return
        
        # Create the cursor, then initialize the DB
        c = conn.cursor()
        c.execute("""CREATE TABLE 'preferences'
            ('id' INTEGER PRIMARY KEY AUTOINCREMENT,
            'preference' text, 'value' text)""")
        conn.commit()
        c.close()
        
        # Now the DB has been created, input some default data there
        self.set('sdkdir', sdkdir)
    
    def get(self, preference):
        "Get value for given preference from the DB"
        
        # Conect to the prefs DB
        try:
            conn = sqlite3.connect(self.dbpath)
        except OperationalError:
            sys.stderr.write("Couldn't open preferences DB sorry\n")
            return 1
        
        c = conn.cursor()
        # execute the query
        t = (preference,)
        c.execute("SELECT value from preferences WHERE preference=? LIMIT 1", t)

        value = c.fetchone()
        conn.commit()
        c.close()
        
        # Preference doesn't exist
        if value == None:
            return ''

        # Return value
        return value[0]
    
    def set(self, preference, value=''):
        """ Set value for given preference from the DB.
        If the preference doesn't already exist, set it"""
        # Conect to the prefs DB
        try:
            conn = sqlite3.connect(self.dbpath)
        except OperationalError:
            sys.stderr.write("Couldn't open preferences DB sorry :(\n")
            return 1
        
        c = conn.cursor()
        # Set or create the VALUE in the DB
        t = (value, preference,)
        if self.get(preference) is '':
            c.execute("INSERT INTO 'preferences' (value, preference) VALUES (?, ?)", t)
        else:
            c.execute("UPDATE 'preferences' set value=? WHERE preference=?", t)
            
        conn.commit()
        c.close()

