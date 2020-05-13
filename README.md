About
-------
For info see http://www.freecadweb.org

Here using:
- archlinux
- opencascade == 7.4.0
- only Path module with dependencies in FreeCAD
- qt          >= 5.14
- python      >= 3.8
- PySide2     == 5.14
- pyside2-tools == 5.14
- shiboken2   == 5.14
- python-six  == 1.13
- boost       == 1.72
- xerces-c    == 3.2.2
- swig        == 4.0.1
- gcc         == 9.2.0


**Use compressed filesystem:**  
dd if=/dev/zero of=image.img iflag=fullblock bs=1M count=150  
mkfs.btrfs ./image.img  
mount -o compress=lzo ./image.img /mnt  
