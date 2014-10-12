#! /usr/bin/python

from optparse import OptionParser
import os, sys

usage = "Usage: %prog [options]"
descr = """Plot profile from grid file"""
parser = OptionParser(usage=usage, description=descr)
parser.add_option("-o", "--output", dest="output", action="store", type="string", nargs=1, default='%s.pdf'%os.path.splitext(sys.argv[0])[0], help="profile output name [default: %default]")
parser.add_option("", "--dpi", dest="dpi", action="store", type="int", nargs=1, default=250, help="number of dpi [default: %default]")

(options, args) = parser.parse_args()

try:
	output = options.output
	oformat  = os.path.splitext(output)[1][1:]
except:
    cmd = '%s --help' % sys.argv[0]
    os.system(cmd)
    sys.exit(1)

from utils import runCommand
import glob

import matplotlib as mpl
mpl.rc('text', usetex=True)

import matplotlib.font_manager as fm
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

main_dir = '.'

fig = plt.figure(1, frameon=False)
DefaultSize = fig.get_size_inches()
fig.set_size_inches( (DefaultSize[0], DefaultSize[1]) )
gs = gridspec.GridSpec(1, 1)

ax = plt.subplot(gs[0, 0], aspect='equal')
ax.set_title(r'Ice thickness comparator')
ax.set_xlabel(r'exact thickness $[\mathrm{m}]$')
ax.set_ylabel(r'estimated thickness $[\mathrm{m}]$')

runCommand('difference.py %s %s > %s' %(os.path.join('target-5.grid'), os.path.join( 'bed.grid'), os.path.join('exact.grid')))
runCommand('grid2surface %s > %s' % (os.path.join( 'exact.grid'), os.path.join( 'exact.xyz')))
data = np.loadtxt(os.path.join( 'exact.xyz'), delimiter='\t')
ze = data[:,2]

os.remove(os.path.join('exact.grid'))
os.remove(os.path.join('exact.xyz'))

runCommand('difference.py %s %s > %s' %(os.path.join( 'target-5.grid'), os.path.join('bedrock.grid'), os.path.join('computed.grid')))
runCommand('grid2surface %s > %s' % (os.path.join('computed.grid'), os.path.join('computed.xyz')))
data = np.loadtxt(os.path.join('computed.xyz'), delimiter='\t')
zc = data[:,2]

id = np.arange(min(ze)-100, max(ze)+100, 10)

plt.xlim(0, max(ze))
plt.ylim(0, max(ze))

cloudc = plt.plot(ze, zc)
plt.setp(cloudc, label='SOA', color='r', marker='+', linestyle='', zorder=2)

os.remove(os.path.join('computed.xyz'))
os.remove(os.path.join('computed.grid'))

idl, = plt.plot(id, id)
plt.setp(idl, color='k', linestyle='-.', linewidth=1.5, zorder=10)

plt.legend(loc='lower right', frameon=False, ncol=1, numpoints=1) # prop=fm.FontProperties(size=10), 

plt.savefig(	'%s' % (output, ), 
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
