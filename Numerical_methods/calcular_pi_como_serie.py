#!/usr/bin/python
# -*- coding: utf8 -*-

n=input ('Teclee un numero')
def Seriepi(x):
	a=float((-1)**x)/float((2*x)+1)
	if x==0:
		return 1
	return a+Seriepi(x-1)
print 4*Seriepi(n)
	
