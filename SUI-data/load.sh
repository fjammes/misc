set -e
set -x

DB=LSST

INPUT_DATA=/data/qserv_testcase04/DC_W13_Stripe82_subset/sui.sql.bzip2.out

MYSQL=$HOME/stack/Linux64/mysql/5.1.65/bin/mysql
MY_SOCK=/data/qserv-run-import/var/lib/mysql/mysql.sock
MY_USER=root
MY_PASS=changeme
# disable ~/.my.cnf
touch ~/.empty.my.cnf
MY_CMD="$MYSQL --defaults-file=~/.empty.my.cnf --socket=$MY_SOCK --user=$MY_USER --pass=$MY_PASS"

# cp /u1/DC_W13_Stripe82_subset/emptyChunks.txt $HOME/qserv-run/2014_12/etc/empty_LSST.txt

# cat <<EOF > version.kvmap
# /css_meta
# /css_meta/version.LOCK
# /css_meta/version       1
# EOF

# cat /u1/DC_W13_Stripe82_subset/metadata.kvmap > metadata.kvmap

# echo "DROP EVERYTHING;RESTORE metadata.kvmap;DUMP EVERYTHING;" | qserv-admin.py

$MY_CMD --execute="CREATE DATABASE IF NOT EXISTS $DB"
$MY_CMD --execute="GRANT SELECT ON $DB.* TO 'qsmaster'@'localhost';"
$MY_CMD "$DB" < "$INPUT_DATA" 
