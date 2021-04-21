# To update the gy-sang version, from a working directory that is clean except for an
# updated doc/release_notes.md file, update the version numbers below. This makefile will
# generate a new version.hpp, *AMEND THE MOST RECENT COMMIT*, and git-tag the commit.

set(GYSANG_VERSION_MAJOR 0)
set(GYSANG_VERSION_MINOR 1)
set(GYSANG_VERSION_PATCHLEVEL 1)

# prefix with - if set
set(GYSANG_VERSION_PRERELEASE_ID "")
# prefix with + if set
set(GYSANG_VERSION_BUILD_METADATA "")
