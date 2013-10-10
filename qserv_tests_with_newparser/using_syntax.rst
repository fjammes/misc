Case 01, Query 0003_selectMetadataForOneGalaxy.sql :
****************************************************

Join between Source an Object :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT s.ra, s.decl, o.raRange, o.declRange FROM   Object o JOIN   Source s USING (objectId) WHERE  o.objectId = 390034570102582 AND    o.latestObsTime = s.taiMidPoint;
  ERROR 4120 (Proxy): Error during execution: 'open failed for chunk(s): 6801 6630 6800 7138 7308 6970 6971 6968 6631 7140read failed for chunk(s): 7478 7648 7310'

xrootd and qserv-master logs are attached and it seems the errors are reported in xrootd.log with SQL sentence like this one :

Log files are available here :

* :download:`xrootd.log </_static/C01_Q0003/xrootd.log>`
* :download:`qserv-master.log </_static/C01_Q0003/qserv-master.log>`

Here's an extract of qserv-master.log :

.. literalinclude:: /_static/C01_Q0003/qserv-master.log
   :language: python
   :lines: 69-82
   :emphasize-lines: 7

Here's an extract of xrootd.log :

.. literalinclude:: /_static/C01_Q0003/xrootd.log
   :language: python
   :lines: 49-60
   :emphasize-lines: 9

It seems that the parser forgot to add the Source table in the FROM clause while rewriting the query.


Case 01, Query 0004_lightCurve.sql
**********************************

Join between Source and Filter :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT taiMidPoint, psfFlux, psfFluxSigma, ra, decl FROM   Source JOIN   Filter USING (filterId) WHERE  objectId = 402412665835716    AND filterName = 'r';
  ERROR 4110 (Proxy): Qserv error: 'mysqld error during index lookup q=SELECT chunkId FROM qservMeta.LSST__Source WHERE objectId IN (402412665835716)'


Log files are available here :

* :download:`xrootd.log </_static/C01_Q0004/xrootd.log>`
* :download:`qserv-master.log </_static/C01_Q0004/qserv-master.log>`

Here the description of qservMeta.LSST__Source table :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> desc LSST__Source;
  +------------+------------+------+-----+---------+-------+
  | Field      | Type       | Null | Key | Default | Extra |
  +------------+------------+------+-----+---------+-------+
  | sourceId   | bigint(20) | NO   | PRI | NULL    |       |
  | chunkId    | int(11)    | YES  |     | NULL    |       |
  | subChunkId | int(11)    | YES  |     | NULL    |       |
  +------------+------------+------+-----+---------+-------+
  3 rows in set (0.00 sec)

Could you please give me the exact structure of LSST_Source table ?
