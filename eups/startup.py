
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
# @LSST UPS@
# and then later:
# lsst_ups @PRODUCT@ @VERSION@ <INSTALL-DIR> [GIT-HASH]
hooks.config.distrib["builder"]["variables"]["LSST UPS"] = """
# copy remote ups directory in installdir
# after having expanded build file
lsst_ups() {
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

