
#!/usr/bin/python

import MySQLdb
import time

dbHost = "127.0.0.1"
dbPort = 13306
dbUser="root"
dbPass = "changeme"
dbName = "qservTest_case04_qserv"

con = MySQLdb.connect(host=dbHost,
                      port=dbPort,
                      user=dbUser,
                      passwd=dbPass,
                      db=dbName,
                      )
cursor = con.cursor()

theCount = 2

def create(nb_lines=theCount):

    # do nothing if data already here
    cursor.execute("DROP TABLE IF EXISTS X1;");
    cursor.execute("SHOW TABLES LIKE 'X1'");
    if not cursor.fetchone():

        sql = ['create table X1 (objectId BIGINT, chunkId INT, subChunkId INT, index(objectId), index(subChunkId)) ENGINE=MyISAM']

        for q in sql:
            print q
            cursor.execute(q)

        oId = 1
        for sChId in range(0, nb_lines):
            for j in range(0, nb_lines):
                cursor.execute('insert into X1 values (%s, 20, %s)',  (oId, sChId))
                cursor.execute('insert into X1 values (%(toto)s, 20, %(tutu)s)', {'toto':oId, 'tutu':sChId})
                oId = oId+1

    cursor.execute("SELECT COUNT(*) FROM X1");
    res=cursor.fetchone()
    print "Lines per table {0}".format(res[0])


create()

cursor.close()
con.close()
