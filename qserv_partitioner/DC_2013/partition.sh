
FILTER=g
INDIR=/data/DC_2013/forcedPhot_csv_dir/${FILTER}/
OUTDIR=/data/DC_2013/forcedPhot_csv_dir_chunked
LOGDIR=${OUTDIR}/log

mkdir -p ${OUTDIR} ${LOGDIR}

RUN_LIST=`ls ${INDIR}`

for run in ${RUN_LIST}
do
    LOGFILE=$LOGDIR/qserv-partition-${FILTER}-${run}.log
    ERRFILE=$LOGDIR/qserv-partition-${FILTER}-${run}.err
    INFILE=${INDIR}/${run}/DeepForcedSource.csv
    FAILFILE=${LOGDIR}/${FILTER}-${run}.FAILED
    if [ -s ${LOGFILE} -a ! -e ${FAILFILE} ]; then
        echo "Already partitioned : ${FILTER} ${run}"
    else
	rm -f ${FAILFILE}
        echo "Partitioning : ${FILTER} ${run}"
        qserv-partition -v -c RunDeepForcedSource.cfg --out.dir=${OUTDIR} -i ${INFILE} 1> ${LOGFILE} 2> ${ERRFILE}
	retcode=$?
	if [ ${retcode} != 0 ]; then
      	    echo "Error (code=${retcode}) during partitionning : ${INFILE}"
	    touch ${FAILFILE}
        fi
    fi
done
