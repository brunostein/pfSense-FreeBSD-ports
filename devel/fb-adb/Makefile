# $FreeBSD$

PORTNAME=	fb-adb
DISTVERSION=	1.4.4-124
DISTVERSIONSUFFIX=	-gb230619
CATEGORIES=	devel

MAINTAINER=	jbeich@FreeBSD.org
COMMENT=	Better shell for Android devices

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	xxd:editors/vim-lite \
		${BASH_CMD}:shells/${BASH_CMD:T}
RUN_DEPENDS=	adb:devel/android-tools-adb

USE_GITHUB=	yes
GH_ACCOUNT=	facebook

USES=		autoreconf gmake ncurses perl5 python:3,build
USE_PERL5=	build # pod2man
BASH_CMD?=	bash # can be zsh
GNU_CONFIGURE=	yes
CONFIGURE_OUTSOURCE=	yes
CONFIGURE_ENV=	PYTHON3="${PYTHON_CMD}"
INSTALL_TARGET=	install-strip
PLIST_FILES=	bin/${PORTNAME} \
		man/man1/${PORTNAME}.1.gz

# Cross-build sanitization
CONFIG_SITE=	/dev/null # XXX Only for AC_CONFIG_SUBDIRS
CONFIGURE_ENV+=	HOST_CFLAGS="${CPPFLAGS} ${CFLAGS:N-[Og]*:N-pipe}" \
		STUB_CFLAGS="${STUB_CFLAGS}" \
		CPPFLAGS="" CFLAGS="${CFLAGS:M-[Og]*} ${CFLAGS:M-pipe}" \
		HOST_LDFLAGS="${LDFLAGS} ${LIBS}" \
		STUB_LDFLAGS="${STUB_LDFLAGS}" \
		LDFLAGS="" LIBS=""

OPTIONS_DEFINE=	ASSERT BASH DEBUG NDK
OPTIONS_DEFAULT=NDK
OPTIONS_EXCLUDE=${ARCH:Namd64:Ni386:C/.+/NDK/}
OPTIONS_EXCLUDE_DragonFly=NDK

ASSERT_CONFIGURE_ENABLE=checking
BASH_DESC=		Install JSON parser used by bash-completion
BASH_RUN_DEPENDS=	jq:textproc/jq
DEBUG_CONFIGURE_ENABLE=	debuggable-stubs

# XXX Convert into USES=android once more things depend on it
NDK_DESC=		Build target stubs using Android NDK
NDK_MASTER_SITES=	https://dl.google.com/android/ndk/:ndk,p7zip
.if defined(ANDROID_NDK)
# Prefer NDK from environment
WRKSRC_ndk=		${ANDROID_NDK}
.else
NDK_DISTFILES=		${NDK_DISTFILES_${LINUX_RPM_ARCH}}
NDK_DISTFILES_i686=	android-ndk-r10e-linux-x86.bin:ndk,p7zip
NDK_DISTFILES_x86_64=	android-ndk-r11c-linux-x86_64.zip:ndk
WRKSRC_ndk=		${WRKDIR}/${NDK_DISTFILES:R:C/(-[^-]+){2}$//}
.endif
NDK_BUILD_DEPENDS=	${LINUX_BASE_PORT}
NDK_USES=		7z:partial
NDK_USE=		LINUX=yes # build
NDK_SHELL=		${SETENV} UNAME_s=Linux UNAME_m=${LINUX_RPM_ARCH} ${SH}
NDK_CONFIGURE_ENV=	ANDROID_NDK="${WRKSRC_ndk}" \
			ANDROID_NDK_SHELL="${NDK_SHELL}" \
			NDK_TMPDIR="${WRKDIR}"
NDK_BUILD_DEPENDS_OFF=	${LOCALBASE}/android/ARMv7/bin/arm-aux-linux-androideabi-gcc:lang/gnatdroid-armv7 \
			${LOCALBASE}/android-x86/x86_32/bin/i686-aux-linux-android-gcc:lang/gnatdroid-x86
.if defined(.PARSEDIR)
NDK_CONFIGURE_ENV_OFF=	PATH="${NDK_BUILD_DEPENDS_OFF:C/:.*//:H:ts:}:$$PATH"
.else
NDK_CONFIGURE_ENV_OFF=	PATH="${LOCALBASE}/android/ARMv7/bin:${LOCALBASE}/android-x86/x86_32/bin:$$PATH"
.endif
NDK_CONFIGURE_OFF=	--with-android-ndk=system

post-extract:
# XXX gold: fatal error: a.out: Invalid argument
	@for f in $$(${FIND} ${WRKSRC_ndk} -type l -name '*-ld'); do \
		(cd $${f%/*} && ${LN} -sf $${f##*/}.bfd $${f##*/}); \
	done

post-patch:
# XXX Decouple -Werror from --enable-checking (ASSERT=on)
	@${REINPLACE_CMD} -e '/CPPFLAGS.*-Werror/d' ${WRKSRC}/configure.ac

post-patch-NDK-off:
	@${REINPLACE_CMD} -i '.aux.bak' -e 's/linux-android/aux-&/' \
		${WRKSRC}/stub-*/configure

.include <bsd.port.mk>

# XXX Bug 204615: Teach USE_LINUX about build-only deps
.if defined(.PARSEDIR)
RUN_DEPENDS:=	${RUN_DEPENDS:N${LINUX_BASE_PORT}}
.else
RUN_DEPENDS:=	${RUN_DEPENDS:N*linux_base*}
.endif
