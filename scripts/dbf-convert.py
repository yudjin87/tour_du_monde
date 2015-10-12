#! /usr/bin/env python
# source: http://home.max-weller.de/journal/2013-05-01/convert-dbase-to-sqlite3/

from dbfpy import dbf
import sys
import os
import sqlite3
import argparse
import re
parser = argparse.ArgumentParser(description="read and convert DBF (dBASE) database files")
group = parser.add_mutually_exclusive_group()
group.add_argument("-f", "--fields", action="store_true", help="display field names")
group.add_argument("-p", "--pretty", action="store_true", help="display pretty-printed table")
group.add_argument("-t", "--table", action="store_true", help="display tab-separated table")
group.add_argument("-d", "--dump", action="store_true", help="dump table")
group.add_argument("-s", "--sqlite", metavar='DB', help="write to sqlite database file DB")
parser.add_argument("-F", "--force", action="store_true", help="overwrites existing table in sqlite database")
parser.add_argument("-v", "--verbose", action="store_true")
parser.add_argument("-i", "--ignore-errors", action="store_true", help="tell DBF library to ignore typecasting errors")
parser.add_argument('infiles', metavar='DBF', nargs='+', help="input files in dBASE (.DBF) format")
args = parser.parse_args()

conn = None

def onIni():
    global conn
    if args.sqlite:
        print "sqlite: Opening db %s ..." % (args.sqlite)
        conn = sqlite3.connect(args.sqlite)
    
    try:
        for dbfName in args.infiles:
            run(dbfName)
    except sqlite3.Error as e:
        print "sqlite: " + e.args[0]
    finally:
        if args.sqlite:
            print "sqlite: Commit and close ..."
            conn.commit()
            conn.close()


def run(dbfName):
    global conn
    dbf1 = dbf.Dbf(dbfName, readOnly=1, ignoreErrors=True)
    
    if args.verbose: print "--> " + dbfName + " <--"
    if args.table:
        for fldName in dbf1.fieldNames:
            sys.stdout.write('%s\t'%(fldName))
        print
        for i1 in range(min(3,len(dbf1))):
            rec = dbf1[i1]
            for fldName in dbf1.fieldNames:
                sys.stdout.write('%s\t'%(rec[fldName]))
            print
            
    elif args.pretty:
        out = [ dbf1.fieldNames ]
        for el in dbf1:
            out.append([ str(s).strip() for s in el ])
        print_table(out)
        
    elif args.sqlite:
        netto_name = os.path.splitext(dbfName)[0]
        print "Importing %s into table %s ..." % (dbfName, netto_name)
        cr_stat = "CREATE TABLE `%s` (`%s`)" % (netto_name, '`,`'.join(dbf1.fieldNames))
        if args.force: conn.execute('DROP TABLE IF EXISTS `%s` ' % (netto_name))
        try:
            conn.execute(cr_stat)
        except Exception, e:
            print "sqlite: Error creating table %s!" % netto_name
            print "You might want to try the --force option."
            raise e
        
        
        for el in dbf1:
            ins_stat = "INSERT INTO `%s` VALUES ('%s')" % (netto_name, "','".join([ str(s).strip().replace("'","''") for s in el ]))
            if args.verbose: print "sqlite: executing: %s" % ins_stat
            conn.execute(ins_stat)
        
    elif args.dump:
        print( "\t%s\t%s\t" % (os.path.getsize(dbfName),dbfName))
        for i1 in range(min(3,len(dbf1))):
            rec = dbf1[i1]
            for fldName in dbf1.fieldNames:
               print('%s: %s'%(fldName, rec[fldName]))
            print
    else:
        sys.stdout.write( "\t%s\t%s\t" % (os.path.getsize(dbfName),dbfName))
        #for i1 in range(min(3,len(dbf1))):
        #    rec = dbf1[i1]
        for fldName in dbf1.fieldNames:
            sys.stdout.write('%s, '%(fldName))
        print
    dbf1.close()


def print_table(rows):
    """print_table(rows)
 
    Prints out a table using the data in `rows`, which is assumed to be a
    sequence of sequences with the 0th element being the header.
    """
 
    # - figure out column widths
    widths = [ len(max(columns, key=len)) for columns in zip(*rows) ]
    
    #widths =  [len(str(max(i, key=lambda x: len(str(x).strip()))).strip()) for i in zip(header, data)]
    #print widths
    
    # - print the separator
    print('+-'+ '-+-'.join( '-' * width for width in widths ) +'-+')
    # - print the header
    header, data = rows[0], rows[1:]
    print('| '+
        ' | '.join( format(title, "%ds" % width) for width, title in zip(widths, header) )
        +' |')
 
    # - print the separator
    print('|-'+ '-+-'.join( '-' * width for width in widths ) +'-|')
 
    # - print the data
    for row in data:
        print('| '+
            " | ".join( format(cdata, "%ds" % width) for width, cdata in zip(widths, row) )
            +' |')

    # - print the separator
    print('+-'+ '-+-'.join( '-' * width for width in widths ) +'-+')

onIni()


