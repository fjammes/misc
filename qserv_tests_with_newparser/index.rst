.. Wide Tables documentation master file, created by
   sphinx-quickstart on Tue Aug 20 16:07:50 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Qserv test queries in error with new parser
===========================================

.. toctree::
   :maxdepth: 2

.. contents::

SQL queries
~~~~~~~~~~~

Case 01, Query 0003_selectMetadataForOneGalaxy.sql :
****************************************************

Join between Source an Object.

.. code-block:: bash
  :emphasize-lines: 1

  mysql> SELECT s.ra, s.decl, o.raRange, o.declRange FROM   Object o JOIN   Source s USING (objectId) WHERE  o.objectId = 390034570102582 AND    o.latestObsTime = s.taiMidPoint;
  ERROR 4120 (Proxy): Error during execution: 'open failed for chunk(s): 6801 6630 6800 7138 7308 6970 6971 6968 6631 7140read failed for chunk(s): 7478 7648 7310'

xrootd and qserv-master logs are attached and it seems the errors are reported in xrootd.log with SQL sentence like this one : 

Log files are available here :

* :download:`xrootd.log </_static/C01_Q0003/xrootd.log>`
* :download:`qserv-master.log </_static/C01_Q0003/qserv-master.log>`

Here's an extract of xrootd.log :

.. literalinclude:: /_static/C01_Q0003/xrootd.log
   :language: python
   :lines: 49-60
   :emphasize-lines: 9

It seems that the parser rewrited the query without adding Source table to the FROM clause.
