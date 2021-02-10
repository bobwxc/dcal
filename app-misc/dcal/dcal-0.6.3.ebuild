# Copyright 2020 Gentoo Authors
# Distributed under the terms of the GNU General Public License v2

EAPI=7

DESCRIPTION="Calculate the days between two given dates."
HOMEPAGE="https://bobwxc.github.io/dcal/"
SRC_URI="https://github.com/bobwxc/${PN}/releases/download/${PV}/${PN}-${PVR}.tar.gz"

LICENSE="MulanPSL-2.0"
SLOT="0"
KEYWORDS="amd64"
IUSE=""

DEPEND=""
RDEPEND="${DEPEND}"
BDEPEND=""

#src_unpack() {
#	ls
#}

src_compile() {
	if [ -f Makefile ] || [ -f GNUmakefile ] || [ -f makefile ]; then
		emake || die "emake failed"
	fi
}

src_install() {
	dobin dcal
	dodoc README.md
}

