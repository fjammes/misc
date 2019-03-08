set -e
set -x

DB=LSST

MYSQL=$HOME/stack/Linux64/mysql/5.1.65/bin/mysql
MYSQLDUMP=$HOME/stack/Linux64/mysql/5.1.65/bin/mysqldump
MY_SOCK=/u/de/fjammes/qserv-run/2014_12/var/lib/mysql/mysql.sock
MY_USER=root
MY_PASS=changeme
MY_CMD="$MYSQL --socket=$MY_SOCK --user=$MY_USER --pass=$MY_PASS $DB"
MY_DUMP_CMD="$MYSQLDUMP --socket=$MY_SOCK --user=$MY_USER --pass=$MY_PASS $DB"

OUTDIR=$HOME/data

rm -f "$OUTDIR"/*.csv "$OUTDIR"/*.schema

for TABLE in DeepCoadd Science_Ccd_Exposure DeepForcedSource_6970 \
    DeepForcedSource_7138 DeepForcedSource_7140 DeepForcedSource_7308 \
    DeepForcedSource_7310 DeepSource_6970 DeepSource_7138 \
    DeepSource_7140 DeepSource_7308 DeepSource_7310
do
    cat <<EOF > sql_$TABLE.txt
SELECT * INTO OUTFILE '$OUTDIR/$TABLE.csv' FIELDS TERMINATED BY ',' ENCLOSED BY '"' ESCAPED BY '\\\\' LINES TERMINATED BY '\n' FROM $TABLE;
EOF
    $MY_CMD < sql_$TABLE.txt

    $MY_DUMP_CMD --no-data "$TABLE" > "$OUTDIR/$TABLE.schema"
done
