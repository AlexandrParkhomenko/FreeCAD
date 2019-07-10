/***************************************************************************
 *   Copyright (c) 2005 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/


#ifndef GUI_SOFCDB_H
#define GUI_SOFCDB_H

#include "stdexport.h"
#include <string>
#include <Inventor/SbBasic.h>

class SoNode;
class SoGroup;
namespace Gui {
/**
 * The FreeCAD database class to initialize all our own Inventor nodes.
 * @author Werner Mayer
 */
class GuiExport SoFCDB
{
public:
    static SbBool isInitialized(void);
    static void init();
    static void finish();
    /// helper to apply a SoWriteAction to a node and write it to a string
    static const std::string& writeNodesToString(SoNode * root);
    static bool writeToVRML(SoNode* node, const char* filename, bool binary);
    // Write to VRML or Inventor file
    static bool writeToFile(SoNode* node, const char* filename, bool binary);
    /*! container for app lifetime storage. See SoFCCSysDragger for details
     * on why this is needed.
     */ 
    static SoGroup* getStorage();
};

} // namespace Gui

#endif // GUI_SOFCDB_H
