
FILTER=g
INDIR=/data/DC_2013/forcedPhot_csv_dir/${FILTER}/
OUTDIR=/data/DC_2013/forcedPhot_csv_dir/chunks

mkdir -p $OUTDIR

RUN_LIST=`ls ${INDIR}`

for run in ${RUN_LIST}
do
    echo "Partitioning : ${FILTER} ${run}"
    qserv-partition -v -c RunDeepForcedSource.cfg --out.dir=${OUTDIR} -i ${INDIR}/${run}/DeepForcedSource.csv >& $OUTDIR/qserv-partition-${FILTER}-${run}.log || touch $OUTDIR/${FILTER}-${run}.FAILED
done
