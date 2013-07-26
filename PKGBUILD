pkgname=dwmstat-git
_gitname=dwmstat
pkgver=2013.07.26
pkgrel=1
pkgdesc="A statusbar for dwm"
arch=('any')
url="https://github.com/at0m5k/dwmstat"
license=('GPL2')
groups=('custom')
depends=('libx11' 'wireless_tools' 'alsa-lib')
makedepends=('git')
source=('git://github.com/at0m5k/dwmstat.git')
md5sums=('SKIP')

pkgver() {
    cd $_gitname
    git log -1 --format="%cd" --date=short | sed 's|-|.|g'
}

build() {
    cd $_gitname
    make
}

package() {
    cd $_gitname
    make PREFIX=/usr DESTDIR="$pkgdir" install
}
