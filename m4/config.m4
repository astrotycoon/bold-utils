dnl
dnl @synopsis SETUP_CONFIG_HEADER
dnl
dnl @summary set up Config/Config.h
dnl
dnl Luba Tang <lubatang@gmail.com>

AC_DEFUN([SETUP_CONFIG_HEADER],
[dnl

AH_TOP([
//===- Config.h.in --------------------------------------------------------===//
//
//                            The Bold Team
//
// This file is distributed under the New BSD License.
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_CONFIG_CONFIG_H
#define BOLD_CONFIG_CONFIG_H
])

AH_BOTTOM([#endif])
])
