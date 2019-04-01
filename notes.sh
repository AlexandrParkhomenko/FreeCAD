# make independent patch
git diff -u old.cpp new.cpp > fix.patch

# get updates
# see commit in browser, add to addres .patch, download file
cd freecad/src/FreeCAD
git apply freecad/patches/*.patch
# or
git apply --ignore-space-change --ignore-whitespace changes.patch

# remove local changes
git stash save --keep-index
git stash drop

# vim force quit
: q!

#move master ref
git reset --soft HEAD~1

