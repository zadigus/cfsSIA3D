#! /usr/bin/python

from optparse import OptionParser
import os, sys

usage = "Usage: %prog [options]"
descr = """Plot glacier contours from grid files"""
parser = OptionParser(usage=usage, description=descr)
parser.add_option("-o", "--output", dest="output", action="store", type="string", nargs=1, default='%s.pdf'%os.path.splitext(sys.argv[0])[0], help="output filename [default: %default]")
parser.add_option("", "--dpi", dest="dpi", action="store", type="int", nargs=1, default=250, help="dpi [default: %default]")

(options, args) = parser.parse_args()

try:
	output   = os.path.splitext(options.output)[0]; assert output
	oformat  = os.path.splitext(options.output)[1][1:]
except:
    cmd = '%s --help' % sys.argv[0]
    os.system(cmd)
    sys.exit(1)

from utils import runCommand
from mesh import getGridPropertiesExt

import glob

import matplotlib.pyplot as plt
import matplotlib as mpl
import matplotlib.font_manager as fm
import matplotlib.gridspec as gridspec
import numpy as np
from math import sqrt

mpl.rc('text', usetex=True)
mpl.rc('font', size=20.0)

main_dir = '.'

fig = plt.figure(1)
DefaultSize = fig.get_size_inches()
fig.set_size_inches((DefaultSize[0]*3, DefaultSize[1]*3))
gs = gridspec.GridSpec(3, 3)

ax = plt.subplot(gs[0:2, 0:2])

ax.set_xlabel(r'$x~[\mathrm{m}]$')
ax.set_ylabel(r'$y~[\mathrm{m}]$')

levels = [1, ]

surface = os.path.join(main_dir, 'surface-2003.grid')
base    = os.path.join(main_dir, 'bed.grid')

runCommand('difference.py %s %s > %s' % (surface, base, 'heightTMP'))
runCommand('grid2grid %s %g %s' % ('heightTMP', 1, 'heightTMP'))
runCommand('grid2surface.py %s' % ('heightTMP', ))
nx, ny, dh, xll, yll = getGridPropertiesExt('heightTMP')
os.remove('heightTMP')

x, y = np.linspace(xll, xll+(nx-1)*dh, nx), np.linspace(yll, yll+(ny-1)*dh, ny)
Y, X = np.meshgrid(y, x)

glacLevels = [0.01, ]

data = np.loadtxt('heightTMP.xyz', delimiter='\t')
os.remove('heightTMP.xyz')    
Z1 = data[:,2]
Z1.shape = (nx, ny)
fmt1 = {}; fmt1[glacLevels[0]] = ''
CS1 = plt.contour(X, Y, Z1, levels=(glacLevels), colors='k', linestyles='-', linewidths=6.0)
plt.clabel(CS1,CS1.levels[::2],inline=False,fontsize=10,manual=False,use_clabeltext=True, fmt=fmt1, zorder=2)
CS1.collections[0].set_label('Glacier contour')

titles = [r'\textbf a', r'\textbf b', r'\textbf c', r'\textbf d', r'\textbf e']

streamNb = [3, 4, 5, 6, 9]

counter=0
for k in streamNb: # plot streamlines in the contour picture
	data = np.loadtxt('99_%02d_bed.xyz'%k)
	try:
		x, y = data[:,0], data[:,1]
	except:
		sys.stderr.write('Streamline %s cannot be used.\n'%streamline)
		continue
	line = plt.plot(x, y)
	plt.setp(line, color='k', linestyle='-', zorder=1)
	ax.text(0.5*(x[0]+x[-1]), 0.5*(y[0]+y[-1]), titles[counter])
	counter+=1

plt.xlim(0, nx*dh)
plt.ylim(0, ny*dh)

colors = ('m', 'g', 'b', 'k')
# Figures
j = 0
while j < 3:
	ax = plt.subplot(gs[j, 2])
	ax.set_title(titles[j], position=(0.98, 0.0))
	k = streamNb[j];
	for f in 'bed', 'target-5':
		runCommand('profile.py %s -l %s > %s'%(os.path.join(main_dir, '%s.grid'%f), '99_%02d_bed.xyz'%k, os.path.join(main_dir, '%s-%d'%(f, k))))

	data = np.loadtxt(os.path.join(main_dir, 'target-5-%d'%k), delimiter='\t')
	X, zt = data[:,0], data[:,1]
	data = np.loadtxt(os.path.join(main_dir, 'bed-%d'%k), delimiter='\t')
	zS = data[:,1]
	lineS, linet, = plt.plot(X, zS, X, zt)
	if j == 1: 
		plt.setp(lineS, label='Solution bedrock topography', color='r', linestyle='-', linewidth=3.0, zorder=1) # estimated surface
		plt.setp(linet, label='Target surface topography', color='k', linestyle='-', linewidth=3.0, zorder=1) # target surface
	else:
		plt.setp(lineS, label='', color='r', linestyle='-', linewidth=3.0, zorder=1) # estimated surface
		plt.setp(linet, label='', color='k', linestyle='-', linewidth=3.0, zorder=1) # target surface

	for f in 'bed', 'target-5', :
		runCommand('rm %s'%os.path.join(main_dir, '%s-%d'%(f, k)))

	cmd = 'profile.py %s -l %s > %s'%(os.path.join('bedrock.grid'), '99_%02d_bed.xyz'%k, os.path.join('bedrock-%d.prof'%k))
	runCommand(cmd)
	data = np.loadtxt(os.path.join('bedrock-%d.prof'%k), delimiter='\t')
	X, zbi = data[:,0], data[:,1]
	line, = plt.plot(X, zbi)
	if j == 1:
		plt.setp(line, label='SOA', color='k', linestyle='--', linewidth=1.0, zorder=2)
	else:
		plt.setp(line, label='', color='k', linestyle='--', linewidth=1.0, zorder=2)
	runCommand('rm %s'%os.path.join(main_dir, 'bedrock-%d.prof'%k))
		
	xmin = X[0]; xmax = X[-1]; 
	plt.xlim(xmin, xmax)
	if j == 1:
		plt.legend(loc='best', frameon=False, bbox_to_anchor=(0.5, 2.5), ncol=3, prop=fm.FontProperties(size=30), numpoints=1)
	j += 1

while j < 5:
	ax = plt.subplot(gs[2, 4-j])
	ax.set_title(titles[j], position=(0.98, 0.))
	k = streamNb[j]; 
	for f in 'bed', 'target-5':
		runCommand('profile.py %s -l %s > %s'%(os.path.join(main_dir, '%s.grid'%f), '99_%02d_bed.xyz'%k, os.path.join(main_dir, '%s-%d'%(f, k))))

	data = np.loadtxt(os.path.join(main_dir, 'target-5-%d'%k), delimiter='\t')
	X, zt = data[:,0], data[:,1]
	data = np.loadtxt(os.path.join(main_dir, 'bed-%d'%k), delimiter='\t')
	zS = data[:,1]
	lineS, linet, = plt.plot(X, zS, X, zt)
	plt.setp(lineS, label='Solution bedrock topography', color='r', linestyle='-', linewidth=3.0, zorder=1) # estimated surface
	plt.setp(linet, label='Target surface topography', color='k', linestyle='-', linewidth=3.0, zorder=1) # target surface

	for f in 'bed', 'target-5', :
		runCommand('rm %s'%os.path.join(main_dir, '%s-%d'%(f, k)))

	runCommand('profile.py %s -l %s > %s'%(os.path.join('bedrock.grid'), '99_%02d_bed.xyz'%k, os.path.join('bedrock-%d.prof'%k)))
	data = np.loadtxt(os.path.join('bedrock-%d.prof'%k), delimiter='\t')
	X, zbi = data[:,0], data[:,1]
	line, = plt.plot(X, zbi)
	plt.setp(line, label='SOA', color='k', linestyle='--', linewidth=1.0, zorder=2)
	runCommand('rm %s'%os.path.join(main_dir, 'bedrock-%d.prof'%k))

	xmin = X[0]; xmax = X[-1];
	plt.xlim(xmin, xmax)
	j += 1

plt.savefig(	'%s.%s' % (output, oformat), 
			format=oformat, 
			dpi=options.dpi, 
			facecolor='w', 
			edgecolor='w', 
			orientation='portrait', 
			papertype=None, 
			transparent=True, 
			bbox_inches=None, 
			pad_inches=0.1)
plt.close(1)

