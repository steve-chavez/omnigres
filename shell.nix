with import (builtins.fetchTarball {
  name = "2023-09-16";
  url = "https://github.com/NixOS/nixpkgs/archive/ae5b96f3ab6aabb60809ab78c2c99f8dd51ee678.tar.gz";
  sha256 = "11fpdcj5xrmmngq0z8gsc3axambqzvyqkfk23jn3qkx9a5x56xxk";
}) {};
mkShell {
  nativeBuildInputs = [
    pugixml openssl
    pkgsStatic.openssl
    uriparser
    h2o
    postgresql_16
  ];
  buildInputs = [
    pkg-config
    cmake
    flex
    readline
    zlib
    clang-tools
    python3
    doxygen
    libpsl
    libuv
    #postgresql_15.withPackages (p: [

    #]);
 ];
  shellHook = ''
    export HISTFILE=.history
  '';
}
