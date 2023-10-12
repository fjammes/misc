#!/bin/bash

set -euxo pipefail

DEST_DIR="/media/fjammes/T7/backup-lpc-home"

echo "Performing backup of home directory"

rsync -avzP --delete $HOME/Documents "$DEST_DIR"
rsync -avzP --delete $HOME/src "$DEST_DIR"
rsync -avzP --delete $HOME/.config "$DEST_DIR"
rsync -avzP --delete $HOME/.ssh "$DEST_DIR"
rsync -avzP --delete $HOME/Dropbox "$DEST_DIR"
rsync -avzP --delete /data/bootmgr.kdbx "$DEST_DIR"