import matplotlib.pyplot as plt
import csv
import numpy
import math
import random

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
		if category not in crunch_categories:
			crunch_categories.append(category)


random.seed(0)

# We need one set of bars / graphs / charts for each result, right?
# Or rather, one for each category...
for category_index, category in enumerate(sorted(crunch_categories)):
	absolutemin = 0xFFFFFFFF
	absolutemax = 0
	
	figure, category_axes = plt.subplots()
	# subplot that represents this category
	#axes = category_axes[category_index]
	axes = category_axes
	bars = []

	for resultindex, result in enumerate(results):
		if category not in result.samples:
			continue
		samples = result.samples[category]
		mean = result.means[category]
		stddev = result.stddevs[category]
		meanerror = result.meanerrors[category]
		yvalues = [resultindex + random.uniform(0.0, 0.50) - 0.25 for y in samples ] 

		color = result.color

		absolutemax = max(absolutemax, result.samplemax[category])
		absolutemin = min(absolutemin, result.samplemin[category])

		bars.append(axes.barh(resultindex, mean, xerr=meanerror, linewidth=0.2, ecolor='black', height=0.50, color=color, align='center', edgecolor='black', alpha=0.85))
		axes.scatter(samples, yvalues, color=color, edgecolor='black', alpha=0.25)
	
	axes.set_title(category)

	absoluterange = absolutemax - absolutemin
	axes.set_xlim([0, absolutemax + (absoluterange * 0.05)])
	axes.set_xlabel('Time (seconds)')

	ylabels = [r.name for r in results]
	yticks = list(range(0, len(results)))
	axes.set_yticks(yticks)
	axes.set_yticklabels([])
	axes.set_ylim([0 - 1, len(ylabels)])
	axes.legend(bars, ylabels, fontsize=10, fancybox=True, loc='best', framealpha=0.5)
	plt.savefig(category + '.png', format='png')


plt.show()
