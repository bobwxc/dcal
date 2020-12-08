# Copyright 2020 Gentoo Authors
# Distributed under the terms of the GNU General Public License v2

EAPI=7

DESCRIPTION="Calculate the days between two given dates."
HOMEPAGE="https://bobwxc.github.io/dcal/"
SRC_URI=""

LICENSE="Mulan PSL v2"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

DEPEND=""
RDEPEND="${DEPEND}"
BDEPEND=""

src_install() {
	emake DESTDIR="${D}" install

	dodoc FAQ NEWS README
}

