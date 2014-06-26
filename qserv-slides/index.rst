
.. DVCS : principe et bonnes pratiques slides file, created by
   hieroglyph-quickstart on Wed Aug 21 10:19:52 2013.

Gestion de projet agile
=======================

* JIRA
* HipChat
* Google Hangout

.. image:: /_static/img/jira.jpeg
   :scale: 50 %
   :align: center

Références
==========

| Jira
| https://jira.lsstcorp.org

|

| Jira : Qserv board
| https://jira.lsstcorp.org/secure/RapidBoard.jspa?rapidView=23&selectedIssue=DM-269

|

| HipChat
| https://lsst.hipchat.com

|

| Utilisation de git pour LSST, Mario Juric
| https://dev.lsstcorp.org/trac/wiki/GitDemoAndTutorial

Interactions distancielles efficaces
====================================

* Meilleure visibilité sur les actions des membres de l'équipes
* Meilleure communication autour des actions de développement
* Meilleure traçabilité et indicateurs

|

.. image:: /_static/img/gitmerge.jpg
   :scale: 100 %
   :align: center

Actions en cours à SLAC
=======================

* Modularisation du code
* Utilisation d'un service de configuration centralisé
* Optimisation du parseur
* Outil de journalisation commun avec le stack
* Intégration de la nouvelle version de xrootd 

|

.. image:: /_static/img/slac_nal_logo.jpg
   :scale: 25 %
   :align: center


Actions en cours à l'IN2P3
==========================

Maintenance et évolution des procédures :

* d'installation, 
* de configuration, (mono-noeud ou autre)
* de tests d'intégration (chargement, exécution, requétage)
|

.. image:: /_static/img/packaging.jpg
   :scale: 50 %
   :align: center



Dans le détail
==============

* Mise en conformité des procédures de gestion des services Qserv avec la LSB : multi-OS
* Mise en conformité de la procédures d'installation avec le nouveau standard LSST : eupspkg
* Procédure de développement/tests généralisé pour l'équipe
* Refonte de l'outil de configuration : isolation des binaires et de l'espace d'exécution
.. image:: /_static/img/lsb.jpg
   :scale: 50 %
   :align: center



Perspectives
============

* Optimisation des métriques des tests d'intégration et du rapport vers l'utilisateur
* Chargement des données de la W14 sur le cluster du CC-IN2P3
* Vers l'intégration continue multi plate-forme avec OpenStack (CC-in2p3)
* Test de Qserv en cours chez Google
