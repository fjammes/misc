
#!/usr/bin/python

import os
import time

import MySQLdb

dbSock = "/data/qserv-run-import/var/lib/mysql/mysql.sock"
dbUser = "root"
dbPass = "changeme"
dbName = "LSST"
dbName = "LSST"

con = MySQLdb.connect(host="127.0.0.1",
                      port=23306,
                      user=dbUser,
                      passwd=dbPass,
                      db=dbName
                      )
cursor = con.cursor()

CHILD = 'DeepForcedSource'
DIRECTOR = 'DeepSource'
TABLES = [ DIRECTOR, CHILD]
CHUNKS = ['6970','7138', '7140', '7308', '7310']

OUTDIR=os.path.join('data', 'qserv_testdata04', 'input')

def diagnose():
    cursor.execute("SHOW DATABASES");
    print cursor.fetchall()
    cursor.execute("SHOW GRANTS FOR CURRENT_USER();")
    print cursor.fetchall()

def alter(tables=TABLES, chunks=CHUNKS):

    sql = ['ALTER TABLE {table} DROP COLUMN IF EXISTS chunkId',
            'ALTER TABLE {table} DROP COLUMN IF EXISTS subChunkId']

    for t in tables:
        for c in chunks:
            for tpl in sql:
                q = tpl.format(table=t+'_'+c)
                print "sql: {0}".format(q)
                cursor.execute(q)

def child_to_outfile(table=CHILD, chunks=CHUNKS, outdir=OUTDIR):

    tpl = ("SELECT f.*, COALESCE(s.ra, f.ra), COALESCE(s.decl, f.decl) "
           "FROM {table} f LEFT JOIN DeepSource s ON (f.deepSourceId = s.deepSourceId) "
           "INTO OUTFILE '{csvfile}'"
           "FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"+'"'
           "' LINES TERMINATED BY '\n'")

    for c in chunks:
        q = tpl.format(table=table, csvfile=os.path.join(outdir,child+'_'+c+'.csv'))
        print "sql: {0}".format(q)
        cursor.execute(q)

def director_to_outfile(table=DIRECTOR, chunks=CHUNKS, outdir=OUTDIR):

    tpl = ("SELECT s.* "
           "FROM {table} s "
           "INTO OUTFILE '{csvfile}' "
           "FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"+'"'
           "' LINES TERMINATED BY '\n'")

    for c in chunks:
        q = tpl.format(table=table, csvfile=os.path.join(outdir,table+'_'+c+'.csv'))
        print "sql: {0}".format(q)
        cursor.execute(q)


# diagnose()
alter()
child_to_outfile()
director_to_outfile()

cursor.close()
con.close()
