Case 01, Query 0010_leapSec.sql :
*********************************

Join between Source an Object :

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


