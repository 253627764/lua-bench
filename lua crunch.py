import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.ticker as mticker
import csv
import numpy
import math
import random
import bisect
import os
import argparse

parser = argparse.ArgumentParser(description='Generate graphs from bench test directory')
parser.add_argument('dir', nargs='?', default=os.getcwd())
args = parser.parse_args()

# The various targets we're going to crunch data for
# ( Name, file, color )
crunch_colors = ['#a6cee3','#1f78b4','#00c9ab','#33a02c',
			  '#fb9a99','#e31a1c','#fdbf6f','#ff7f00',
			  '#cab2d6','#6a3d9a','#ffff99', '#f5f5f5', 
			  '#b15928', '#b2df8a', '#cc33cc'
]

crunch_targets = [
	( "lua-intf", os.path.join( args.dir, "lua bench tests lua-intf.csv" ), crunch_colors[0] ),
	( "luabind", os.path.join( args.dir, "lua bench tests luabind.csv" ), crunch_colors[1] ),
	( "lua-api-pp", os.path.join( args.dir, "lua bench tests lua-api-pp.csv" ), crunch_colors[2] ),
	( "luacppinterface", os.path.join( args.dir, "lua bench tests luacppinterface.csv" ), crunch_colors[3] ),
	( "luawrapper", os.path.join( args.dir, "lua bench tests luawrapper.csv" ), crunch_colors[4] ),
	( "selene", os.path.join( args.dir, "lua bench tests selene.csv" ), crunch_colors[5] ),
	( "slb3", os.path.join( args.dir, "lua bench tests slb3.csv" ), crunch_colors[6] ),
	( "swig", os.path.join( args.dir, "lua bench tests swig.csv" ), crunch_colors[7] ),
	( "oolua", os.path.join( args.dir, "lua bench tests oolua.csv" ), crunch_colors[8] ),
	( "kaguya", os.path.join( args.dir, "lua bench tests kaguya.csv" ), crunch_colors[9] ),
	( "sol", os.path.join( args.dir, "lua bench tests sol.csv" ), crunch_colors[10] ),
	( "old sol", os.path.join( args.dir, "lua bench tests old-sol.csv" ), crunch_colors[11] ),
	( "luwra", os.path.join( args.dir, "lua bench tests luwra.csv" ), crunch_colors[12] ),
	( "plain C", os.path.join( args.dir, "lua bench tests plain C.csv" ), crunch_colors[13] ),
	( "lualite", os.path.join( args.dir, "lua bench tests lualite.csv" ), crunch_colors[14] ),
]
timescale = [
	("picoseconds",  1e-12,      1e+12),
	("nanoseconds",  1e-9,       1e+9),
	("microseconds", .00001,    1000000),
	("milliseconds", .001,      1000),
	("seconds",      1,          1),
	("minutes",      60,         1/60),
]
timescalevalues = [x[1] for x in timescale]

class benchmark_result:
	def __init__(self, name, file, color):
		self.name = name
		self.file = file
		self.color = color
		self.means = {}
		self.stddevs = {}
		self.clippingranges = {}
		self.meanerrors = {}
		self.samples = {}
		self.samplemin = {}
		self.samplemax = {}
		self.visiblesamples = {}
		self.visiblesamplemin = {}
		self.visiblesamplemax = {}
		self.absolutemin = 0xFFFFFFFF
		self.absolutemax = 0
		self.process()

	def process(self):
		with open(self.file) as filehandle:
			rows = csv.DictReader(filehandle)
			for row in rows:
				for fieldname in rows.fieldnames:
					# massage key data to have similar names
					# Could just change the C++ source to name it as desired... ?
					# Nah, error messages from nonius only take benchmark name,
					# and there's no "grouping" or "header" functionality, so...
					k = fieldname
					v = row[fieldname]
					k = str(k).strip()
					splits = k.split(' - ', 1)
					if len(splits) > 1:
						k = splits[1]
					v = float(v) / 100.0
					# append into right place
					target = None

					if k in self.samples:
						target = self.samples[k]
					else:
						target = []
						self.samples[k] = target
						self.samplemin[k] = 0xFFFFFFFF
						self.samplemax[k] = 0
					mintarget = self.samplemin[k];
					maxtarget = self.samplemax[k];
					target.append(v)
					self.samplemax[k] = max(self.samplemax[k], v)
					self.samplemin[k] = min(self.samplemin[k], v)
					self.absolutemax = max(self.absolutemax, v)
					self.absolutemin = min(self.absolutemin, v)
					
			for result in self.samples:
				self.means[result] = numpy.average(self.samples[result])
				self.stddevs[result] = numpy.std(self.samples[result], ddof = 1)
				self.meanerrors[result] = self.means[result] / math.sqrt(len(self.samples))
				self.clippingranges[result] = (max(self.means[result] + (self.stddevs[result] * -1.8), 0), self.means[result] + (self.stddevs[result] * 1.8))
				self.visiblesamples[result] = [ y for y in self.samples[result] if self.clippingranges[result][0] <= y <= self.clippingranges[result][1] ]
				self.visiblesamplemax[result] = max(self.visiblesamples[result])
				self.visiblesamplemin[result] = min(self.visiblesamples[result])

			
crunch_categories = []
results = []

print("Starting lua crunch graphers...")

for t in crunch_targets:
	if not os.path.exists(t[1]):
		print("Skipping {}, {} does not exist".format(t[0], t[1]))
		continue
	print("Crunching {}, from {}".format(t[0], t[1]))
	b = benchmark_result(t[0], t[1], t[2])
	results.append(b)
	for category in b.samples:
		match = next((x for x in crunch_categories if x[0] == category), None)
		if match is None:
			crunch_categories.append([category, b.means[category], b.samplemax[category], b.samplemin[category]])
		else:
			if b.name == 'plain C':
				match[1] = b.means[category]
			match[2] = max(match[2], b.visiblesamplemax[category])
			match[3] = min(match[3], b.visiblesamplemin[category])


random.seed(0)

# We need one set of bars / graphs / charts for each result, right?
# Or rather, one for each category...
for category_index, category_info in enumerate(sorted(crunch_categories, key=lambda x: x[0])):
	category = category_info[0]
	categorybaseline = category_info[1]
	categorymax = category_info[2]
	categorymin = category_info[3]
	
	figure, categoryaxes = plt.subplots()
	# subplot that represents this category
	axes = categoryaxes
	absoluterange = categorymax - categorymin
	bars = []
	barlabels = []
	def by_mean(x):
		if category not in x.samples:
			return float('inf')
		return x.means[category]

	for resultindex, result in enumerate(sorted(results, key=by_mean, reverse=True)):
		color = result.color
		name = result.name

		if category not in result.samples:
			bars.append(axes.text(absoluterange * 0.02, resultindex, 'unsupported', color=color, style='italic', horizontalalignment='left', verticalalignment='center', fontsize='small'))
			barlabels.append(name)
			continue

		xvalues = result.samples[category]
		mean = result.means[category]
		stddev = result.stddevs[category]
		meanerror = result.meanerrors[category]
		yvalues = [resultindex + random.uniform(0.0, 0.50) - 0.25 for y in xvalues] 

		bars.append(axes.barh(resultindex, mean, xerr=meanerror, linewidth=0.2, ecolor='black', height=0.50, color=color, align='center', edgecolor='black', alpha=0.85))
		barlabels.append(name)
		axes.scatter(xvalues, yvalues, color=color, edgecolor='black', alpha=0.25)
	
	bars = list(reversed(bars))
	axes.set_title(category)

	xscaleindex = bisect.bisect_left(timescalevalues, categorymax)
	xscale = timescale[xscaleindex - 1]
	def fmt ( value, pos ):
		if value == 0:
			return '0'
		if value.is_integer():
			return '{0:.0f}'.format(value * xscale[2])
		return '{0:.2f}'.format(value * xscale[2])

	axes.set_xlim([0, categorymax + (absoluterange * 0.05)])
	axes.set_xlabel('execution time (' + xscale[0] + ') - lower is better')
	axes.xaxis.set_major_formatter(mticker.FuncFormatter(fmt))

	ylabels = [r.name for r in results]
	yticks = list(range(0, len(results)))
	axes.set_yticks(yticks)
	axes.set_ylim([0 - 1, len(ylabels)])
	axes.set_yticklabels(barlabels)
	# better to label the axes than have a legend
	#axes.set_yticklabels([])
	#axes.legend(bars, barlabels, fontsize=10, fancybox=True, loc='best', framealpha=0.5)
	
	# red line is ugly, as Puppy pointed out... I tend to agree, but still... 
	# muh baseline qq
	#axes.axvline(x = categorybaseline, linewidth=1, color='r', alpha=0.7)
	
	# Ensure tight layout
	figure.tight_layout()
	savetarget = 'lua bench graph - ' + category + '.png'
	print("Saving graph: {} (to - '{}')".format(category, savetarget))
	plt.savefig(savetarget, format='png')
	plt.close(figure)


#plt.show()
