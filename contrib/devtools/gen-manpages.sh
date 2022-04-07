#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SHAHEPAYD=${SHAHEPAYD:-$SRCDIR/shahepayd}
SHAHEPAYCLI=${SHAHEPAYCLI:-$SRCDIR/shahepay-cli}
SHAHEPAYTX=${SHAHEPAYTX:-$SRCDIR/shahepay-tx}
SHAHEPAYQT=${SHAHEPAYQT:-$SRCDIR/qt/shahepay-qt}

[ ! -x $SHAHEPAYD ] && echo "$SHAHEPAYD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
SHAHEVER=($($SHAHEPAYCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for shahepayd if --version-string is not set,
# but has different outcomes for shahepay-qt and shahepay-cli.
echo "[COPYRIGHT]" > footer.h2m
$SHAHEPAYD --version | sed -n '1!p' >> footer.h2m

for cmd in $SHAHEPAYD $SHAHEPAYCLI $SHAHEPAYTX $SHAHEPAYQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${SHAHEVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${SHAHEVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
