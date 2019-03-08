
#!/usr/bin/python

import MySQLdb
import time

dbHost = "127.0.0.1"
dbPort = 13306
dbUser="root"
dbPass = "changeme"
dbName = "compIdx"

con = MySQLdb.connect(host=dbHost,
                      port=dbPort,
                      user=dbUser,
                      passwd=dbPass,
                      db=dbName,
                      )
cursor = con.cursor()

theCount = 300

def create(nb_lines=theCount):

    # do nothing if data already here
    cursor.execute("SHOW TABLES LIKE 'X1'");
    if not cursor.fetchone():

        sql = ['create table X1 (objectId BIGINT, chunkId INT, subChunkId INT, index(objectId), index(subChunkId)) ENGINE=MyISAM',
               'create table X2 (objectId BIGINT, chunkId INT, subChunkId INT, index(objectId, subChunkId)) ENGINE=MyISAM',
               'create table X3 (objectId BIGINT, chunkId INT, subChunkId INT, index(subChunkId, objectId)) ENGINE=MyISAM']

        for q in sql:
            print q
            cursor.execute(q)

        oId = 1
        for sChId in range(0, nb_lines):
            for j in range(0, nb_lines):
                cursor.execute('insert into X1 values (%d, 20, %d)' % (oId, sChId))
                cursor.execute('insert into X2 values (%d, 20, %d)' % (oId, sChId))
                cursor.execute('insert into X3 values (%d, 20, %d)' % (oId, sChId))
                oId = oId+1

    cursor.execute("SELECT COUNT(*) FROM X1");
    res=cursor.fetchone()
    print "Lines per table {0}".format(res[0])

def createSubQ(table, sChId):
    return ['select * from {0} where subChunkId = {1}'.format(table, sChId)]

def rawNN(table, sChId):
    select = 'select o1.objectId, o2.objectId from %s o1, %s o2 ' % (table, table)
    where = 'where o1.subChunkId = {0} and o2.subChunkId = {1} and o1.objectId <> o2.objectId'.format(sChId, sChId)
    qList = [select + where]
    return qList

def jitNN(table, sChId, inMem=False):
    tt = 'dummy';

    make = ["CREATE TABLE {0} SELECT * FROM {1} WHERE subChunkId = {2}".format(tt, table, sChId)]
    makeMem = ["CREATE TABLE {0} like {1} ENGINE=memory".format(tt, table),
               "INSERT INTO {0} SELECT * FROM {1} WHERE subChunkId = {2}".format(tt, table, sChId)]

    nn = rawNN(tt, sChId)
    destroy = ["DROP TABLE %s" % (tt)]
    if inMem:
        return makeMem + nn + destroy
    else:
        return make + nn + destroy


def test(qFunc, table, times=theCount):
    startTime = time.time()
    print "Launching {0}, {1} times against {2}".format(qFunc(table,"%s"), times, table)
    for sChId in range(times):
        q = qFunc(table, sChId)
        for qi in q:
            cursor.execute(qi)
    elapsedTime = time.time() - startTime
    print "Elapsed time {1}\n".format(table, elapsedTime)

def testSubQ(table):
    test(createSubQ, table)


create()
testSubQ('X1')
testSubQ('X2')
testSubQ('X3')
testSubQ('X1')
testSubQ('X2')
testSubQ('X3')

test(rawNN, 'X1', 10)
test(rawNN, 'X2', 10)
test(rawNN, 'X3', 10)

test(jitNN, 'X1', 10)
test(jitNN, 'X2', 10)
test(jitNN, 'X3', 10)

cursor.close()
con.close()
