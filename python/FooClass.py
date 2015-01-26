#!/usr/bin/env python
# coding=utf-8

class FooClass(object):
    """my very first class: FooClass"""
    version = 0.1 # class (data) attribute
    def __init__(self, nm = 'lnmcc'):
        """constructor"""
        self.name = nm #class instance (data) attribute
        print 'Created a class instance for', nm

    def showname(self):
        """display instance attrbute and class name"""
        print 'You name is ', self.name
        print 'My name is ', self.__class__.__name__

    def showver(self):
        """display class(static) attribute"""
        print self.version # references FooClass.version

fool = FooClass()

