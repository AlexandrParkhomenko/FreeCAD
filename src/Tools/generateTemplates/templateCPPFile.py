#! python
# -*- coding: utf-8 -*-
# (c) 2006 Juergen Riegel 

import template
import generateBase.generateModel_Module
import generateBase.generateTools

class TemplateCPPFile (template.ModelTemplate):
  def Generate(self):
    generateBase.generateTools.ensureDir(self.path)
    print ("Generate() App Dir")

Template = """
/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
 *   FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY                         *
 ***************************************************************************/

"""
