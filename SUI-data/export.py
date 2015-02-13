
#!/usr/bin/python

import os
import time

import MySQLdb

dbSock = "/data/qserv-run-import/var/lib/mysql/mysql.sock"
dbUser = "root"
dbPass = "changeme"
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
LIMIT = 1000

OUTDIR=os.path.join('/', 'data', 'qserv_testcase04', 'input')

def diagnose():
    cursor.execute("SHOW DATABASES");
    print cursor.fetchall()
    cursor.execute("SHOW GRANTS FOR CURRENT_USER();")
    print cursor.fetchall()

def alter(tables=TABLES, chunks=CHUNKS):

    sql = ['ALTER TABLE {table} DROP COLUMN chunkId',
            'ALTER TABLE {table} DROP COLUMN subChunkId']

    for t in tables:
        for c in chunks:
            for tpl in sql:
                q = tpl.format(table=t+'_'+c)
                print "sql: {0}".format(q)
                cursor.execute(q)

def _chunks_to_oufile(tpl, chunks, table, outdir, limit):

    tpl += ("INTO OUTFILE '{csvfile}' "
            "FIELDS TERMINATED BY ',' OPTIONALLY ENCLOSED BY '"+'"'
            "' LINES TERMINATED BY '\n'")

    for c in chunks:
        csvfile = os.path.join(outdir,
                               "{table}_{chunk}_{limit}.csv".format(table=table,
                                                                    chunk=c,
                                                                    limit=limit))
        try:
            os.remove(csvfile)
        except OSError:
            pass

        q = tpl.format(table=table+"_"+c, csvfile=csvfile)
        print "sql: {0}".format(q)
        cursor.execute(q)

def child_to_outfile(table=CHILD, director=DIRECTOR, chunks=CHUNKS, outdir=OUTDIR, limit=LIMIT):

    if limit:
        tpl_join = ("(SELECT d.* from {director} d limit {limit})")
        join_type="INNER"
    else:
        tpl_join = "{director}"
        join_type="LEFT"
    sql_join = tpl_join.format(director=director, limit=limit)

    tpl = ("SELECT f.*, COALESCE(s.ra, f.ra), COALESCE(s.decl, f.decl) "
           "FROM {table} f "
           + join_type + " JOIN "
           + sql_join + " s "
           "ON (f.deepSourceId = s.deepSourceId) ")

    _chunks_to_oufile(tpl, chunks, table, outdir, limit)

def director_to_outfile(table=DIRECTOR, chunks=CHUNKS, outdir=OUTDIR, limit=LIMIT):

    tpl = ("SELECT s.* "
           "FROM {table} s ")

    if limit:
        tpl += "LIMIT {limit} ".format(limit=limit)

    _chunks_to_oufile(tpl, chunks, table, outdir, limit)

# diagnose()
# alter()
child_to_outfile()
director_to_outfile()

cursor.close()
con.close()
