#! /usr/bin/python

from optparse import OptionParser
import os, sys

usage = "Usage: %prog [options]"
descr = """Plot profile from grid file"""
parser = OptionParser(usage=usage, description=descr)
parser.add_option("-o", "--output", dest="output", action="store", type="string", nargs=1, default='%s.png'%os.path.splitext(sys.argv[0])[0], help="profile output name [default: %default]")
parser.add_option("", "--dpi", dest="dpi", action="store", type="int", nargs=1, default=250, help="number of dpi [default: %default]")
parser.add_option("", "--legend", dest="key", action="store", type="string", nargs=1, default=None, help="position of the legend in the picture ('best', 'upper right', 'bottom left', etc.) [default: %default]")
parser.add_option("", "--transparent", dest="transparent", action="store_true", default=False, help="enable transparent background [default: %default]")
#parser.add_option("", "--latex-preamble", dest="preamble", action="store", type="string", default='/home/lmichel/Documents/reports/optimisation/preamble', help="path to latex preamble [default: %default]")
parser.add_option("", "--show", dest="show", action="store_true", default=False, help="Show image or save to file [default: %default]")

(options, args) = parser.parse_args()

try:
	output  = os.path.splitext(options.output)[0]; assert output
	oformat  = os.path.splitext(options.output)[1][1:]
except:
    cmd = '%s --help' % sys.argv[0]
    os.system(cmd)
    sys.exit(1)

from utils import runCommand
from mesh import getGridProperties
import glob

import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.gridspec as gridspec
import matplotlib.font_manager as fm
import matplotlib.cm as cm
import numpy as np
import matplotlib.colors as mcolors
import math

mpl.rc('text', usetex=True)
#mpl.rc('text.latex', preamble=r'\input{'+options.preamble+r'}')

fig = plt.figure(1)
fig.set_frameon(False)
gs = gridspec.GridSpec(2, 2)

DH = [100, 50, 25, 12.5]
DT = [0.1, 0.05, 0.025, 0.0125]

for scheme in 'fully', : 
	for tf in 1, 10, : 
		for i in range(0, 2):
			for j in range(0, 2):
				k = j+2*i;

				ax = plt.subplot(gs[i, j])
				ax.set_title(r'$\Delta x=%g~\mathrm{m}, \Delta t=%g~\mathrm{a}$'%(DH[k], DT[k]))
				ax.set_xlabel(r'$x [\mathrm{m}]$')
				ax.set_ylabel(r'$y [\mathrm{m}]$')
				ax.yaxis.set_major_locator(mpl.ticker.MaxNLocator(4))
				ax.xaxis.set_major_locator(mpl.ticker.MaxNLocator(4))

				nbIter = 1./DT[k]*tf
				runCommand('difference.py %s %s > %s'%(os.path.join('tf=%g-dh=%g'%(tf, DH[k]), '%s-%010d'%(scheme, nbIter)), 'surface-%g-tf=%g.grid'%(DH[k], tf), 'diffS'))
				runCommand('grid2surface %s > %s'%('diffS', 'diffS.xyz'))

				nx, ny, dh = getGridProperties('diffS')

				x, y = np.linspace(0, (nx-1)*dh, nx), np.linspace(0, (ny-1)*dh, ny)
				Y, X = np.meshgrid(y, x)

				data = np.loadtxt('diffS.xyz', delimiter='\t')
				os.remove('diffS.xyz')
				Zh = data[:,2]
				Zh.shape = (nx, ny)

				boundz = 20
				levs = np.arange(0, boundz, 0.1)

				#plt.contour(X, Y, abs(Zh), levels=levs, linewidths = 0.0, colors = 'k')
				plt.pcolormesh(X, Y, abs(Zh), cmap='gist_yarg')

				cb = plt.colorbar() # draw colorbar

				if j==1:
					ax.set_ylabel('')
					for t in ax.yaxis.get_ticklabels():
						t.set_visible(False)
					cb.set_label(r'$\mathcal H-\mathcal H_{\mathrm{Halfar}}~[\mathrm{m}]$')

				if i==0:
					ax.set_xlabel('')
					for t in ax.xaxis.get_ticklabels():
						t.set_visible(False)

			plt.savefig(	'HalfarConvergence-%s-%g.%s' % (scheme, tf, oformat), 
					format=oformat, 
					dpi=options.dpi, 
					facecolor='w', 
					edgecolor='w', 
					orientation='portrait', 
					papertype=None, 
					transparent=options.transparent, 
					bbox_inches=None, 
					pad_inches=0.1)
		plt.close(1)

