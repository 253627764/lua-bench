import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.ticker as mticker
import csv
import numpy
import math
import random
import bisect

# The various targets we're going to crunch data for
# ( Name, file, color )
crunch_colors = ['#a6cee3','#1f78b4','#b2df8a','#33a02c','#fb9a99','#e31a1c','#fdbf6f','#ff7f00','#cab2d6','#6a3d9a','#ffff99','#b15928']
crunch_targets = [
	( "lua-intf", "lua - results/lua bench tests lua-intf.csv", crunch_colors[0] ),
	( "luabind", "lua - results/lua bench tests luabind.csv", crunch_colors[1] ),
	( "lua-api-pp", "lua - results/lua bench tests lua-api-pp.csv", crunch_colors[2] ),
	( "luacppinterface", "lua - results/lua bench tests luacppinterface.csv", crunch_colors[3] ),
	( "luawrapper", "lua - results/lua bench tests luawrapper.csv", crunch_colors[4] ),
	( "selene", "lua - results/lua bench tests selene.csv", crunch_colors[7] ),
	( "slb3", "lua - results/lua bench tests slb3.csv", crunch_colors[8] ),
	( "swig", "lua - results/lua bench tests swig.csv", crunch_colors[10] ),
	( "oolua", "lua - results/lua bench tests oolua.csv", crunch_colors[5] ),
	( "sol", "lua - results/lua bench tests sol.csv", crunch_colors[9] ),
	( "luwra", "lua - results/lua bench tests luwra.csv", crunch_colors[11] ),
	( "plain C", "lua - results/lua bench tests plain C.csv", crunch_colors[6] ),
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
		self.meanerrors = {}
		self.samples = {}
		self.samplemin = {}
		self.samplemax = {}
		self.absolutemin = 0xFFFFFFFF
		self.absolutemax = 0
		self.process()

	def process(self):
		with open(self.file) as filehandle:
			rows = csv.DictReader(filehandle)
			for row in rows:
				for fieldname in rows.fieldnames:
					# massage key data to have similar names
					# TODO: Could just change the C++ source to name it as desired... ?
					k = fieldname
					v = row[fieldname]
					k = str(k).strip()
					splits = k.split(' - ', 1)
					if len(splits) > 1:
						k = splits[1]
					v = float(v)
					# append into right place
					target = None

					if fieldname in self.samples:
						target = self.samples[fieldname]
					else:
						target = []
						self.samples[fieldname] = target
						self.samplemin[fieldname] = 0xFFFFFFFF
						self.samplemax[fieldname] = 0
					mintarget = self.samplemin[fieldname];
					maxtarget = self.samplemax[fieldname];
					target.append(v)
					self.samplemax[fieldname] = max(self.samplemax[fieldname], v)
					self.samplemin[fieldname] = min(self.samplemin[fieldname], v)
					self.absolutemax = max(self.absolutemax, v)
					self.absolutemin = min(self.absolutemin, v)
					
			for result in self.samples:
				self.means[result] = numpy.average(self.samples[result])
				self.stddevs[result] = numpy.std(self.samples[result], ddof = 1)
				self.meanerrors[result] = self.means[result] / math.sqrt(len(self.samples))

			
crunch_categories = []
results = []

for t in crunch_targets:
	b = benchmark_result(t[0], t[1], t[2])
	results.append(b)
	for category in b.samples:
		match = next((x for x in crunch_categories if x[0] == category), None)
		if match is None:
			crunch_categories.append([category, b.samplemax[category], b.samplemin[category]])
		else:
			match[1] = max(match[1], b.samplemax[category])
			match[2] = min(match[2], b.samplemin[category])


random.seed(0)

# We need one set of bars / graphs / charts for each result, right?
# Or rather, one for each category...
for category_index, category_info in enumerate(sorted(crunch_categories, key=lambda x: x[0])):
	category = category_info[0]
	categorymax = category_info[1]
	categorymin = category_info[2]
	
	figure, categoryaxes = plt.subplots()
	# subplot that represents this category
	axes = categoryaxes
	bars = []
	barlabels = []
	basemeanline = None

	for resultindex, result in enumerate(results):
		color = result.color
		name = result.name
		if category not in result.samples:
			bars.append(mpatches.Patch(color=color))
			barlabels.append(name)
			continue
		
		samples = result.samples[category]
		mean = result.means[category]
		if name == 'plain C':
			basemeanline = mean
		stddev = result.stddevs[category]
		meanerror = result.meanerrors[category]
		yvalues = [resultindex + random.uniform(0.0, 0.50) - 0.25 for y in samples ] 

		bars.append(axes.barh(resultindex, mean, xerr=meanerror, linewidth=0.2, ecolor='black', height=0.50, color=color, align='center', edgecolor='black', alpha=0.85))
		barlabels.append(name)
		axes.scatter(samples, yvalues, color=color, edgecolor='black', alpha=0.25)
	
	bars = list(reversed(bars))
	barlabels = list(reversed(barlabels))
	axes.set_title(category)

	absoluterange = categorymax - categorymin
	xscaleindex = bisect.bisect_left(timescalevalues, categorymax)
	xscale = timescale[xscaleindex - 1]
	def fmt ( value, pos ):
		return '{0:.2f}'.format(value * xscale[2])

	axes.set_xlim([0, categorymax + (absoluterange * 0.05)])
	axes.set_xlabel('execution time (' + xscale[0] + ')')
	axes.xaxis.set_major_formatter(mticker.FuncFormatter(fmt))

	ylabels = [r.name for r in results]
	yticks = list(range(0, len(results)))
	axes.set_yticks(yticks)
	axes.set_ylim([0 - 1, len(ylabels)])
	axes.set_yticklabels(reversed(barlabels))
	# better to label the axes than have a legend
	#axes.set_yticklabels([])
	#axes.legend(bars, barlabels, fontsize=10, fancybox=True, loc='best', framealpha=0.5)
	
	if basemeanline is not None:
		axes.axvline(x = basemeanline, linewidth=1, color='r', alpha=0.7)
	
	# Ensure tight layout
	figure.tight_layout()
	plt.savefig('lua bench graph - ' + category + '.png', format='png')
	plt.close(figure)


plt.show()
