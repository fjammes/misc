Case 01, Query 0010_leapSec.sql :
*********************************

Sub-query in WHERE clause :

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT offset, mjdRef, drift FROM LeapSeconds  WHERE whenUtc = (         SELECT MAX(whenUtc)          FROM LeapSeconds          WHERE whenUtc <=  NAME_CONST('nsecs_',39900600000000000000000000)                 );
  Added one
  got work.
  ERROR 4120 (Proxy): Error during execution: 'open failed for chunk(s): 6800 6801read failed for chunk(s): 7310 7308 6968 6971 7140 6630 6970 7648 7478 7138 6631'


Log files are available here :

* :download:`xrootd.log </_static/C01_Q0010/xrootd.log>`
* :download:`qserv-master.log </_static/C01_Q0010/qserv-master.log>`

Here's some interesting extracts of xrootd.log :

.. literalinclude:: /_static/C01_Q0010/xrootd.log
   :language: python
   :lines: 86-91
   :emphasize-lines: 2

.. literalinclude:: /_static/C01_Q0010/xrootd.log
   :language: python
   :lines: 103-111
   :emphasize-lines: 2

It looks like the parser hasn't completely re-written the sub-query.

The same type of error happen for **3009_subquery.sql** :
 
.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT src.sourceId FROM Source src WHERE src.objectId IN (   SELECT objectId   FROM Object o   WHERE ra_PS  BETWEEN 0. AND 1.    AND decl_PS BETWEEN 0. AND 1.  );
  ERROR 4120 (Proxy): Error during execution: 'read failed for chunk(s): 7140 6971 7308 7310 7478 6970 6631 6630 6801 7138 7648 6800 6968'

.. code-block:: bash
  :emphasize-lines: 2

  0 WriteSpawn Thu Oct 10 16:34:38 2013 0.000103
  >>You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ')' at line 1 Unable to execute query: CREATE TABLE r_1d28893fddbeec5969fb3cc95df28d3d8_6970_0 SELECT src.sourceId,objectId FROM LSST.Object_6970 AS o WHERE src.objectId IN();
  <<---Error with piece 0 complete (size=1).
  File write(0) at 0 for 144 by qsmaster
  TIMING,q_3421QueryBuildSubFinish,1381415678


