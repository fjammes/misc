Case 01, Query 0012_raftAndCcd.sql :
************************************

Query with parenthesis in where clause fails in Qserv :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT sce.filterId, sce.filterName FROM   Science_Ccd_Exposure AS sce WHERE  (sce.visit = 887404831) AND (sce.raftName = '3,3') AND (sce.ccdName LIKE '%');
  ERROR 4120 (Proxy): Error during execution: 'open failed for chunk(s): 7138 6800 6970read failed for chunk(s): 7310 7140 6631 7648 6630 6971 7478 7308 6968 6801'


whereas it returns a result without parentheses :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT sce.filterId, sce.filterName FROM   Science_Ccd_Exposure AS sce WHERE  sce.visit = 887404831 AND sce.raftName = '3,3' AND sce.ccdName LIKE '%';
  +----------+------------+
  | filterId | filterName |
  +----------+------------+
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  ...
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  +----------+------------+
  52 rows in set (1.49 sec)

Nevertheless, the previous query launched againt a simple mysql server returns only 4 rows :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT sce.filterId, sce.filterName FROM   Science_Ccd_Exposure AS sce WHERE  (sce.visit = 887404831) AND (sce.raftName = '3,3') AND (sce.ccdName LIKE '%');
  +----------+------------+
  | filterId | filterName |
  +----------+------------+
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  |        3 | i          |
  +----------+------------+
  4 rows in set (0.01 sec)


Log files for the first query are available here :

* :download:`xrootd.log </_static/C01_Q0012/xrootd.log>`
* :download:`qserv-master.log </_static/C01_Q0012/qserv-master.log>`


Here's an extract of xrootd.log :

.. literalinclude:: /_static/C01_Q0012/xrootd.log
   :language: python
   :lines: 166-173
   :emphasize-lines: 2

Here's an extract of qserv-master.log :

.. literalinclude:: /_static/C01_Q0012/qserv-master.log
   :language: python
   :lines: 9261-9270
   :emphasize-lines: 2

Please note that the same type of error seems to occur with query 2001_fullObjectScan.sql : 

.. code-block:: sql 

  -- Full table scan for Object table with some cuts.
  --
  -- Similar queries:
  --
  -- * Find quasars 
  --   http://dev.lsstcorp.org/trac/wiki/dbQuery018
  --
  -- * Low-z QSO candidates using the color cuts
  --   http://dev.lsstcorp.org/trac/wiki/dbQuery020
  --
  -- * Find high proper motion white dwarf candidates
  --   http://dev.lsstcorp.org/trac/wiki/dbQuery026
  --
  -- * Find extremely red galaxies
  --   http://dev.lsstcorp.org/trac/wiki/dbQuery037


  SELECT objectId,
       scisql_fluxToAbMag(uFlux_PS),
       scisql_fluxToAbMag(gFlux_PS),
       scisql_fluxToAbMag(rFlux_PS),
       scisql_fluxToAbMag(iFlux_PS),
       scisql_fluxToAbMag(zFlux_PS),
       scisql_fluxToAbMag(yFlux_PS),
       ra_PS, decl_PS
  FROM   Object
  WHERE  ( scisql_fluxToAbMag(gFlux_PS)-scisql_fluxToAbMag(rFlux_PS) > 0.7 OR 
         scisql_fluxToAbMag(gFlux_PS) > 22.3 )
  AND    scisql_fluxToAbMag(gFlux_PS)-scisql_fluxToAbMag(rFlux_PS) > 0.1
  AND    ( scisql_fluxToAbMag(rFlux_PS)-scisql_fluxToAbMag(iFlux_PS) < 
         (0.08 + 0.42 * (scisql_fluxToAbMag(gFlux_PS)-scisql_fluxToAbMag(rFlux_PS) - 0.96)) 
        OR scisql_fluxToAbMag(gFlux_PS)-scisql_fluxToAbMag(rFlux_PS) > 1.26 )
  AND    scisql_fluxToAbMag(iFlux_PS)-scisql_fluxToAbMag(zFlux_PS) < 0.8
  ORDER BY objectId
