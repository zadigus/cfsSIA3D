#! /usr/bin/python

from optparse import OptionParser
import os, sys

usage = "Usage: %prog [options]"
descr = """Plot glacier contours from grid files"""
parser = OptionParser(usage=usage, description=descr)
parser.add_option("-o", "--output", dest="output", action="store", type="string", nargs=1, default='%s.pdf'%os.path.splitext(sys.argv[0])[0], help="output filename [default: %default]")
parser.add_option("", "--dpi", dest="dpi", action="store", type="int", nargs=1, default=250, help="dpi [default: %default]")
parser.add_option("", "--transparent", dest="transparent", action="store_true", default=False, help="enable transparent background [default: %default]")
#parser.add_option("", "--latex-preamble", dest="preamble", action="store", type="string", default='/home/lmichel/Documents/reports/optimisation/preamble', help="path to latex preamble [default: %default]")
parser.add_option("", "--show", dest="show", action="store_true", default=False, help="Show image or save to file [default: %default]")

(options, args) = parser.parse_args()

try:
	output   = os.path.splitext(options.output)[0]; assert output
	oformat  = os.path.splitext(options.output)[1][1:]
except:
    cmd = '%s --help' % sys.argv[0]
    os.system(cmd)
    sys.exit(1)

from utils import runCommand
from mesh import getGridProperties

import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.font_manager as fm
import matplotlib.gridspec as gridspec
import numpy as np
from math import sqrt

mpl.rc('text', usetex=True)
#mpl.rc('text.latex', preamble=r'\input{'+options.preamble+r'}')
mpl.rc('font', size=20.0)

fig = plt.figure(1)
DefaultSize = fig.get_size_inches()
fig.set_size_inches((DefaultSize[0]*3, DefaultSize[1]*2))
gs = gridspec.GridSpec(2, 3)

Dh = 200
Dt = 0.2
scheme = 'fully'
colors = ('k', 'r', 'g', 'b', 'm')
# Figures
k=0
for tf in 1, 10: 
	j=0
	for y in 2250, 3000, 3750 :
		ax = plt.subplot(gs[k, j])
		ax.set_title(r'$y=%g~\mathrm{m}$'%y)
		if not j:
			ax.set_ylabel(r'$t_f=%g~\mathrm{a}$'%tf)
		profile = 'profile-y=%g'%y
		for f in 'base-12.5.grid', 'surface-12.5-tf=%g.grid'%tf, :
			runCommand('profile.py %s -l %s > %s'%(f, 'profile-y=%g'%y, '%s-y=%g'%(f, y)))
			data = np.loadtxt('%s-y=%g'%(f, y))
			X, Z = data[:,0], data[:,1]
			line = plt.plot(X, Z)
			plt.setp(line, color='k', linestyle='-', linewidth=3.0, zorder=1)
		dh = Dh
		dt = Dt
		for i in range(0, 4):
			dh /= 2.
			dt /= 2.
			nbIter = 1./dt*tf
			f = os.path.join('tf=%g-dh=%g'%(tf, dh), '%s-%010d'%(scheme, nbIter))
			runCommand('profile.py %s -l %s > %s'%(f, 'profile-y=%g'%y, '%s-y=%g'%(f, y)))
			data = np.loadtxt('%s-y=%g'%(f, y))
			X, Z = data[:,0], data[:,1]
			line = plt.plot(X, Z)
			plt.setp(line, linewidth=1.0, zorder=2, label=r'$\Delta x = %g~\mathrm{m}$'%dh)

		if j == 2:
			plt.legend(loc='best', ncol=1, prop=fm.FontProperties(size=20), numpoints=1, frameon=False)
		j += 1
	k += 1

plt.savefig(	'%s.%s' % (output, oformat), 
			format=oformat, 
			dpi=options.dpi, 
			facecolor='w', 
			edgecolor='w', 
			orientation='portrait', 
			papertype=None, 
			transparent=True, #options.transparent, 
			bbox_inches=None, 
			pad_inches=0.1)
plt.close(1)

