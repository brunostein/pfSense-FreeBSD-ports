# $FreeBSD$

PORTNAME=	fbopenssl
PORTVERSION=	0.0.4
CATEGORIES=	security
MASTER_SITES=	SF/modgssapache/${PORTNAME}/${PORTVERSION}/

MAINTAINER=	ports@FreeBSD.org
COMMENT=	GSS-API and SPNEGO extensions for OpenSSL

LICENSE=	GPLv2

USES=		uidfix
USE_LDCONFIG=	yes
USE_OPENSSL=	yes
MAKEFILE=	BSDMakefile
MAKE_ENV=	BSD_INSTALL_DATA="${BSD_INSTALL_DATA}"
WRKSRC=		${WRKDIR}/${PORTNAME}
PORTDOCS=	readme.txt

.if defined(NO_PROFILE)
PLIST_SUB+=	PROFILE="@comment "
.else
PLIST_SUB+=	PROFILE=""
.endif

OPTIONS_DEFINE=	DOCS

post-extract:
	${INSTALL_DATA} ${FILESDIR}/BSDMakefile ${WRKSRC}

post-install:
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_DATA} ${WRKSRC}/readme.txt ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>
