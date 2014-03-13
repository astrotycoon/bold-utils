#!/bin/bash
#                       The Bold Project
#
#  This file is distributed under the New BSD License.
#  See LICENSE for details.
#
# Author: Luba Tang <luba@skymizer.com>

function gettop() 
{
  local TOPFILE=tools/bold/main.cpp
  if [ -n "${BOLDTOP}" -a -f "${BOLDTOP}/${TOPFILE}" ]; then
    echo ${BOLDTOP}
  else
    if [ -f "${TOPFILE}" ]; then
      echo `pwd`;
    else
      local HERE=$PWD
      T=
      while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
        cd .. > /dev/null
        T=`PWD= pwd`
      done
      cd $HERE > /dev/null
      if [ -f "${T}/${TOPFILE}" ]; then
        echo ${T}
      fi
    fi
  fi
}

function count_loc()
{
  local H=`find ${BOLDTOP} | grep '\.h'`
  local T=`find ${BOLDTOP} | grep '\.tcc'`
  local C=`find ${BOLDTOP} | grep '\.cpp'`
  wc ${C} ${H} ${T}
}

#############################
#  Variable Dictionary
export BOLDTOP=$(gettop)
export PATH="${BOLDTOP}/scripts/bin:$PATH"

