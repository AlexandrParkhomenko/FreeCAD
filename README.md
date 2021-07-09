About
-------
For info see http://www.freecadweb.org

Here using:
- archlinux
- opencascade == 7.5
- only Path module with dependencies in FreeCAD
- qt          >= 5.15
- python      >= 3.9
- PySide2     == 5.15
- pyside2-tools == 5.15
- shiboken2   == 5.15
- python-six  == 1.15
- boost       == 1.76
- xerces-c    == 3.2
- swig        == 4.0
- gcc         == 10.2


**Use compressed filesystem:**  
dd if=/dev/zero of=image.img iflag=fullblock bs=1M count=150  
mkfs.btrfs ./image.img  
mount -o compress=lzo ./image.img /mnt  
