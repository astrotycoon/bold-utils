#!/bin/bash
#
#                    The Bold Team
#
#  This file is distributed under the New BSD License.
#  See LICENSE for details.

function build
{
  local VERSION=$1
  local CONFIG=$2
  local BUILDDIR=./build-${VERSION}-${CONFIG}

  if [ -d ${BUILDDIR} ]; then
    rm -rf ${BUILDDIR}
  fi

  mkdir ${BUILDDIR}
  cd ${BUILDDIR}
  ../${VERSION}/autogen.sh

  if [ "${CONFIG}" = "dbg" ]; then
    ../${VERSION}/configure --prefix=${HOME}/Skymizer/SysRoot --enable-unittest
  elif [ "${CONFIG}" = "opt" ]; then
    ../${VERSION}/configure --prefix=${HOME}/Skymizer/SysRoot --enable-optimize
  else
    ../${VERSION}/configure --prefix=${HOME}/Skymizer/SysRoot
  fi

  make all install

  cd -
}

if [ $# != 2 ] && [ $# != 1 ]; then
  echo "Usage: $0 [source folder] [dbg|opt|normal]"
  exit 1;
fi

SRCDIR=$(basename $1)
TRGDIR=$2

if [ -z "${TRGDIR}" ]; then
  TRGDIR="normal"
fi

if [ "${TRGDIR}" != "dbg" ] && [ "${TRGDIR}" != "opt" ] && [ "${TRGDIR}" != "normal" ]; then
  echo "Usage: $0 [source folder] [dbg|opt|normal]"
  exit 1;
fi

build ${SRCDIR} ${TRGDIR}

