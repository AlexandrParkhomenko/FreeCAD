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
: q!

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

