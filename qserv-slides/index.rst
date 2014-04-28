
.. DVCS : principe et bonnes pratiques slides file, created by
   hieroglyph-quickstart on Wed Aug 21 10:19:52 2013.

=================================================
 . . . Qserv
=================================================

.. figure:: /_static/img/arton292.png
   :class: fill

Gestion de projet agile
=======================

* JIRA
* HipChat
* Google Hangout ?

.. image:: /_static/img/jira.jpeg
   :scale: 75 %
   :align: center

Interactions distancielles efficaces
====================================

* Meilleure visibilité sur les actions des membres de l'équipes
* Meilleure communication autour des actions de développement
* Meilleure traçabilité et indicateurs

|

.. image:: /_static/img/gitmerge.jpg
   :scale: 75 %
   :align: center

Actions en cours à SLAC
=======================

* Modularisation du code
* Utilisation d'un service de configuration centralisé
* Optimisation du parseur
* Outil de journalisation commun avec le stack
* Optimisation de xrootd 

|

.. image:: /_static/img/slac_nal_logo.jpg
   :scale: 25 %
   :align: center


Actions en cours à l'IN2P3
==========================

Maintenance et évolution des procédures :

* d'installation, 
* de configuration, (mono-noeud pour l'instant)
* de tests d'intégration (chargement, exécution, requétage)
|

.. image:: /_static/img/packaging.jpg
   :scale: 50 %
   :align: center



Dans le détail
==============

* Intégration et validation des fonctionnalités développées à SLAC (modules, zookeeper, partitioner)
* Mise en conformité des procédures de gestion des services Qserv avec la LSB : multi-OS
* Mise en conformité de la procédures d'installation avec le nouveau standard LSST : eupspkg

Perspectives
============

Discussion à venir avec Mario Juric pour l'amélioration du standard logiciel LSST :

* Script newinstall.sh
* Gestion des dépendances systèmes avec eups
* Automatisation de la procédure de distribution, avec le support des branches git de développement
* Vers l'intégration continue multi plate-forme avec Docker et OpenStack (CC-in2p3) ?

Références
==========

| Jira
| https://jira.lsstcorp.org

| Jira : Qserv board
| https://jira.lsstcorp.org/secure/RapidBoard.jspa?rapidView=23&selectedIssue=DM-269

| HipChat
| https://lsst.hipchat.com

| Utilisation de git pour LSST, Mario Juric
| https://dev.lsstcorp.org/trac/wiki/GitDemoAndTutorial

Questions
=========

.. image:: /_static/img/hackaton_Apr2014.jpg
   :scale: 70 %
   :align: center
