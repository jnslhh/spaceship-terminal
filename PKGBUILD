# Maintainer: Andrey Scherbakov <andreyscherbakov@example.com>
pkgname=spaceship-terminal
pkgver=1.0.0
pkgrel=1
pkgdesc="A retro terminal spaceship animation in C++ using ncursesw"
arch=('x86_64')
url="https://github.com/dudll300/spaceship-terminal"
license=('MIT')
depends=('ncurses')
makedepends=('make' 'gcc')
source=("${pkgname}-${pkgver}.tar.gz::${url}/archive/refs/tags/v${pkgver}.tar.gz")
sha256sums=('SKIP')

build() {
	cd "spaceship-${pkgver}"
	make
}

package() {
	cd "spaceship-${pkgver}"
	make DESTDIR="${pkgdir}" PREFIX=/usr install
	install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
	install -Dm644 README.md "${pkgdir}/usr/share/doc/${pkgname}/README.md"
}
