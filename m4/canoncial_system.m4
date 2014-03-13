dnl
dnl @synopsis CHECK_CANONICAL_SYSTEM
dnl
dnl @summary set up default value of `host`, `build` and `target`
dnl
dnl Luba Tang <lubatang@gmail.com>

AC_DEFUN([CHECK_CANONICAL_SYSTEM],
[dnl

AC_CANONICAL_HOST

AC_CACHE_CHECK([type of operating system we're going to host on],
  [bold_cv_host_os_type],
  [case $host in
  *-*-aix*)
    bold_cv_host_os_type="AIX"
    bold_cv_host_platform_type="Unix" ;;
  *-*-irix*)
    bold_cv_host_os_type="IRIX"
    bold_cv_host_platform_type="Unix" ;;
  *-*-cygwin*)
    bold_cv_host_os_type="Cygwin"
    bold_cv_host_platform_type="Unix" ;;
  *-*-darwin*)
    bold_cv_host_os_type="Darwin"
    bold_cv_host_platform_type="Unix" ;;
  *-*-minix*)
    bold_cv_host_os_type="Minix"
    bold_cv_host_platform_type="Unix" ;;
  *-*-freebsd*)
    bold_cv_host_os_type="FreeBSD"
    bold_cv_host_platform_type="Unix" ;;
  *-*-openbsd*)
    bold_cv_host_os_type="OpenBSD"
    bold_cv_host_platform_type="Unix" ;;
  *-*-netbsd*)
    bold_cv_host_os_type="NetBSD"
    bold_cv_host_platform_type="Unix" ;;
  *-*-dragonfly*)
    bold_cv_host_os_type="DragonFly"
    bold_cv_host_platform_type="Unix" ;;
  *-*-hpux*)
    bold_cv_host_os_type="HP-UX"
    bold_cv_host_platform_type="Unix" ;;
  *-*-interix*)
    bold_cv_host_os_type="Interix"
    bold_cv_host_platform_type="Unix" ;;
  *-*-linux*)
    bold_cv_host_os_type="Linux"
    bold_cv_host_platform_type="Unix" ;;
  *-*-solaris*)
    bold_cv_host_os_type="SunOS"
    bold_cv_host_platform_type="Unix" ;;
  *-*-auroraux*)
    bold_cv_host_os_type="AuroraUX"
    bold_cv_host_platform_type="Unix" ;;
  *-*-win32*)
    bold_cv_host_os_type="Win32"
    bold_cv_host_platform_type="Win32" ;;
  *-*-mingw*)
    bold_cv_host_os_type="MingW"
    bold_cv_host_platform_type="Win32" ;;
  *-*-haiku*)
    bold_cv_host_os_type="Haiku"
    bold_cv_host_platform_type="Unix" ;;
  *-unknown-eabi*)
    bold_cv_host_os_type="Freestanding"
    bold_cv_host_platform_type="Unix" ;;
  *-unknown-elf*)
    bold_cv_host_os_type="Freestanding"
    bold_cv_host_platform_type="Unix" ;;
  *)
    bold_cv_host_os_type="Unknown"
    bold_cv_host_platform_type="Unknown" ;;
  esac])

dnl Set the "OS" Makefile variable based on the platform type so the
dnl makefile can configure itself to specific build hosts
if test "$bold_cv_host_os_type" = "Unknown" ; then
  AC_MSG_ERROR([Operating system is unknown, configure can't continue])
fi

dnl Set the "BOLD_ON_*" variables based on llvm_cv_llvm_cv_platform_type
dnl This is used by lib/Support to determine the basic kind of implementation
dnl to use.
case $bold_cv_host_platform_type in
Unix)
  AC_DEFINE([BOLD_ON_UNIX],[1],[Define if this is Unixish platform])
  AC_SUBST(BOLD_ON_PLATFORM,[BOLD_ON_UNIX])
;;
Win32)
  AC_DEFINE([BOLD_ON_WIN32],[1],[Define if this is Win32ish platform])
  AC_SUBST(BOLD_ON_PLATFORM,[BOLD_ON_WIN32])
;;
esac

AC_SUBST(HOST_OS,$bold_cv_host_os_type)

AC_CANONICAL_TARGET
AC_CACHE_CHECK([type of operating system we're going to target],
  [bold_cv_target_os_type],
  [case $target in
  *-*-aix*)
    bold_cv_target_os_type="AIX" ;;
  *-*-irix*)
    bold_cv_target_os_type="IRIX" ;;
  *-*-cygwin*)
    bold_cv_target_os_type="Cygwin" ;;
  *-*-darwin*)
  bold_cv_target_os_type="Darwin" ;;
  *-*-minix*)
    bold_cv_target_os_type="Minix" ;;
  *-*-freebsd* | *-*-kfreebsd-gnu)
    bold_cv_target_os_type="FreeBSD" ;;
  *-*-openbsd*)
    bold_cv_target_os_type="OpenBSD" ;;
  *-*-netbsd*)
    bold_cv_target_os_type="NetBSD" ;;
  *-*-dragonfly*)
    bold_cv_target_os_type="DragonFly" ;;
  *-*-hpux*)
    bold_cv_target_os_type="HP-UX" ;;
  *-*-interix*)
    bold_cv_target_os_type="Interix" ;;
  *-*-linux*)
    bold_cv_target_os_type="Linux" ;;
  *-*-gnu*)
    bold_cv_target_os_type="GNU" ;;
  *-*-solaris*)
    bold_cv_target_os_type="SunOS" ;;
  *-*-auroraux*)
    bold_cv_target_os_type="AuroraUX" ;;
  *-*-win32*)
    bold_cv_target_os_type="Win32" ;;
  *-*-mingw*)
    bold_cv_target_os_type="MingW" ;;
  *-*-haiku*)
    bold_cv_target_os_type="Haiku" ;;
  *-*-rtems*)
    bold_cv_target_os_type="RTEMS" ;;
  *-*-nacl*)
    bold_cv_target_os_type="NativeClient" ;;
  *-unknown-eabi*)
    bold_cv_target_os_type="Freestanding" ;;
  *)
    bold_cv_target_os_type="Unknown" ;;
  esac])

if test "$bold_cv_target_os_type" = "Unknown" ; then
  AC_MSG_WARN([Configuring for an unknown target operating system])
fi

AC_SUBST(TARGET_OS,$bold_cv_target_os_type)

AC_CACHE_CHECK([target architecture],
  [bold_cv_target_arch_type],
  [case $target in
  i?86-*)                 bold_cv_target_arch_type="x86" ;;
  amd64-* | x86_64-*)     bold_cv_target_arch_type="x86_64" ;;
  sparc*-*)               bold_cv_target_arch_type="Sparc" ;;
  powerpc*-*)             bold_cv_target_arch_type="PowerPC" ;;
  arm*-*)                 bold_cv_target_arch_type="ARM" ;;
  aarch64*-*)             bold_cv_target_arch_type="AArch64" ;;
  mips-* | mips64-*)      bold_cv_target_arch_type="Mips" ;;
  mipsel-* | mips64el-*)  bold_cv_target_arch_type="Mips" ;;
  xcore-*)                bold_cv_target_arch_type="XCore" ;;
  msp430-*)               bold_cv_target_arch_type="MSP430" ;;
  hexagon-*)              bold_cv_target_arch_type="Hexagon" ;;
  mblaze-*)               bold_cv_target_arch_type="MBlaze" ;;
  nvptx-*)                bold_cv_target_arch_type="NVPTX" ;;
  *)                      bold_cv_target_arch_type="Unknown" ;;
  esac])

if test "$bold_cv_target_arch_type" = "Unknown" ; then
  AC_MSG_WARN([Configuring for an unknown target archicture])
fi

AC_SUBST(TARGET_ARCH,$bold_cv_target_arch_type)

dnl Set the "BOLD_DEFAULT_TARGET_TRIPLE" variable based on $target.
dnl This is used to determine the default target triple and emulation
dnl to use.
AC_DEFINE([BOLD_DEFAULT_TARGET_TRIPLE],
          [$target],
          [default target triple])

])
