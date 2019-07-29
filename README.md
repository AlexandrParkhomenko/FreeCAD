About
-------
For info see http://www.freecadweb.org

Here using:
- archlinux
- opencascade == 7.3.0
- only Path module with dependencies in FreeCAD
- qt          >= 5.13
- python      >= 3.7
- PySide2     == 5.13
- pyside2-tools == 5.13
- shiboken2   == 5.13
- python-six  == 1.12
- boost       == 1.69
- xerces-c    == 3.2.2
- swig        == 4.0.0
- gcc         == 9.1.0


**Use compressed filesystem:**  
dd if=/dev/zero of=image.img iflag=fullblock bs=1M count=150  
mkfs.btrfs ./image.img  
mount -o compress=lzo ./image.img /mnt  
