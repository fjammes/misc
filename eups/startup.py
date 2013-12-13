
hooks.config.Eups.colorize = True

def cmdHook(Eups, cmd, opts, args):
    if cmd.split()[0] == "distrib":
        subcmd = cmd.split()[1]
        if subcmd == "create":
            opts.distribTypeName = "builder"
            opts.allowIncomplete = True
            opts.useFlavor = "generic"
            opts.serverDir = "~/tmp/pkgroot"

eups.commandCallbacks.add(cmdHook)

# How to install "ups" files for LSST third-party products (grab from git)
#
# Third-party products' build files should contain at the top:
# @QSERV UPS@
# and then later:
# qserv_ups @PRODUCT@ @VERSION@ <INSTALL-DIR> [GIT-HASH]
hooks.config.distrib["builder"]["variables"]["QSERV UPS"] = """
# copy remote ups directory in installdir
# after having expanded build file
qserv_ups() {
    if [ -z "$1" -o -z "$2" -o -z "$3" ]; then
        echo "lsst_ups requires at least three arguments"
        exit 1
    fi
    productname=$1
    versionname=$2
    installdir=$3
    githash=$4
    gitrepo="~/misc/"
    if [ -z "$githash" ]; then
        githash="HEAD"
    fi
    currentdir=$(pwd)
    eups_files="eups/pkg/${productname}/${versionname}/ups"
    git archive --verbose --format=tar --remote=$gitrepo --prefix=tmp/ ${githash} ${eups_files} | tar --extract --verbose --directory $installdir &&
    mkdir -p $installdir/ups &&
    mv $installdir/tmp/$eups_files/* $installdir/ups/ &&
    rm -rf $installdir/tmp &&
    echo "eups expandbuild -i ${installdir}/ups/${productname}.build -V $versionname "
    eups expandbuild -i ${installdir}/ups/${productname}.build -V $versionname 
    git archive --verbose --format=tar --remote=$gitrepo --prefix=ups/ ${githash} ${productname} | tar --extract --verbose --directory $installdir || echo "No additional files required: ignore error"
}
"""

# @QSERV PREPARE@
# and then later:
# qserv_prepare @PRODUCT@ @VERSION@
hooks.config.distrib["builder"]["variables"]["QSERV PREPARE"] = """
# download and extract archive source file
# and goes in its top directory
qserv_prepare() {
    if [ -z "$1" -o -z "$2" ]; then
        echo "qserv_prepare requires at least two arguments"
        exit 1
    fi

    url=http://www.slac.stanford.edu/exp/lsst/qserv/download/current
    
    productname=$1
    versionname=$2

    extractname=${productname}-${versionname}

    if [ -z "$3" ]; 
    then
        archivename=${extractname}.tar.gz
    else
	archivename=$3-${versionname}.tar.gz
    fi

    curl -L ${url}/${archivename} > ${archivename} &&
    mkdir ${extractname} && 
    tar xf ${archivename} -C ${extractname} --strip-components 1 &&
    product_dir=$(eups path 0)/$(eups flavor)/${productname}/${versionname} &&
    cd ${extractname}
}
"""
