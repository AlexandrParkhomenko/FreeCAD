################################################################################
#  Copyright (c) Victor Titov (DeepSOIC)
#  (vv.titov@gmail.com) 2016
#  FreeCAD LICENSE IS LGPL3 WITHOUT ANY WARRANTY
################################################################################
import FreeCAD as App

def getAllDependencies(feat):
    '''getAllDependencies(feat): gets all features feat depends on, directly or indirectly. 
    Returns a list, with deepest dependencies last. feat is not included in the list, except 
    if the feature depends on itself (dependency loop).'''
    list_traversing_now = [feat]
    set_of_deps = set()
    list_of_deps = []
    
    while len(list_traversing_now) > 0:
        list_to_be_traversed_next = []
        for feat in list_traversing_now:
            for dep in feat.OutList:
                if not (dep in set_of_deps):
                    set_of_deps.add(dep)
                    list_of_deps.append(dep)
                    list_to_be_traversed_next.append(dep)
        
        list_traversing_now = list_to_be_traversed_next
    
    return list_of_deps

def getAllDependent(feat):
    '''getAllDependent(feat): gets all features that depend on feat, directly or indirectly. 
    Returns a list, with deepest dependencies last. feat is not included in the list, except 
    if the feature depends on itself (dependency loop).'''
    list_traversing_now = [feat]
    set_of_deps = set()
    list_of_deps = []
    
    while len(list_traversing_now) > 0:
        list_to_be_traversed_next = []
        for feat in list_traversing_now:
            for dep in feat.InList:
                if not (dep in set_of_deps):
                    set_of_deps.add(dep)
                    list_of_deps.append(dep)
                    list_to_be_traversed_next.append(dep)
        
        list_traversing_now = list_to_be_traversed_next
    
    return list_of_deps

def isContainer(obj):
    '''isContainer(obj): returns True if obj is an object container, such as 
    Group, Part, Body. The important characterisic of an object being a 
    container is visibility nesting.'''
    
    if obj.hasExtension('App::OriginGroupExtension'):
        return True
    if obj.hasExtension('App::GroupExtension'):
        return True
    if obj.isDerivedFrom('App::Origin'):
        return True
    return False
