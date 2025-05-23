PORTNAME=	lightdm-gtk-greeter
PORTVERSION=	2.0.9
CATEGORIES=	x11
MASTER_SITES=	https://github.com/Xubuntu/${PORTNAME}/releases/download/${PORTNAME}-${PORTVERSION}/

MAINTAINER=	desktop@FreeBSD.org
COMMENT=	GTK greeter for LightDM
WWW=		https://github.com/Xubuntu/lightdm-gtk-greeter

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	xdt-csource:devel/xfce4-dev-tools
LIB_DEPENDS=	liblightdm-gobject-1.so:x11/lightdm
RUN_DEPENDS=	at-spi2-core>0:accessibility/at-spi2-core

USES=		gettext-tools gmake gnome localbase pkgconfig xorg
USE_CSTD=	c99
USE_GNOME=	cairo gdkpixbuf gtk30 intltool
USE_XORG=	x11

GNU_CONFIGURE=	yes
SUB_FILES=	pkg-deinstall pkg-install

CONFIGURE_ARGS+=	--enable-at-spi-command=${LOCALBASE}/libexec/at-spi-bus-launcher

OPTIONS_DEFINE=	DOCS LIBINDICATOR NLS
OPTIONS_SUB=	yes

LIBINDICATOR_DESC=	Desktop indicators support
LIBINDICATOR_ENABLE=	libindicator
LIBINDICATOR_LIB_DEPENDS=	libindicator3.so:devel/libindicator

NLS_USES=		gettext-runtime
NLS_CONFIGURE_ENABLE=	nls

post-install:
	(cd ${STAGEDIR}${PREFIX}/etc/lightdm && ${MV} lightdm-gtk-greeter.conf \
		lightdm-gtk-greeter.conf.sample)

.include <bsd.port.mk>
