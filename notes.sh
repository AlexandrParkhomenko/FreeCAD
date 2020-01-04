# make independent patch
git diff -u old.cpp new.cpp > fix.patch

# get updates
# see commit in browser, add to addres .patch, download file
cd freecad/src/FreeCAD
git apply freecad/patches/*.patch
# or
git apply --recount --ignore-space-change  --whitespace=fix changes.patch

# remove local changes
git stash save --keep-index
git stash drop

# vim force quit
:q!
# vim save&quit
:wq

#move master ref
git reset --soft HEAD~1
git push --force
#this commands is better
git diff HEAD HEAD~1 > revert.patch
git apply revert.patch

#How to undo (almost) anything
  #public
  git revert <SHA>
  #local
  git checkout


sed -i "/^\s*\/\/ /d"  "${outfile}" # delete c-onestring-comments
sed -i "/^[/*]\*/d"  "${outfile}" # delete /* ** */

#cmake
FIND_PROGRAM(PYSIDE2UICBINARY NAMES pyuic5)
FIND_PROGRAM(PYSIDE2RCCBINARY NAMES pyrcc5)

