# Maintainer: Andrey Scherbakov <andreyscherbakov@example.com>
pkgname=spaceship-terminal
pkgver=1.0.0
pkgrel=1
pkgdesc="A retro terminal spaceship animation in C++ using ncursesw"
arch=('x86_64')
url="https://github.com/andreyscherbakov/spaceship"
license=('MIT')
depends=('ncurses')
makedepends=('make' 'gcc')
source=("git+${url}.git")
sha256sums=('SKIP')

build() {
	cd "${srcdir}/${pkgname}"
	make
}

package() {
	cd "${srcdir}/${pkgname}"
	install -Dm755 spaceship "${pkgdir}/usr/bin/spaceship"
}
