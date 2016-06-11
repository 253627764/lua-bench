import matplotlib.pyplot as plt
import csv
import numpy
import math

# The various targets we're going to crunch data for
# ( Name, file, Data )
crunch_targets = [
	( "lua-intf", "lua - results/lua bench tests lua-intf.csv", "#000000" ),
	( "luabind", "lua - results/lua bench tests luabind.csv", "#000000" ),
	( "lua-api-pp", "lua - results/lua bench tests lua-api-pp.csv", "#000000" ),
	( "luacppinterface", "lua - results/lua bench tests luacppinterface.csv", "#000000" ),
	( "luawrapper", "lua - results/lua bench tests luawrapper.csv", "#000000" ),
	( "oolua", "lua - results/lua bench tests oolua.csv", "#000000" ),
	( "plain C", "lua - results/lua bench tests plain C.csv", "#000000" ),
	( "selene", "lua - results/lua bench tests selene.csv", "#000000" ),
	( "slb3", "lua - results/lua bench tests slb3.csv", "#000000" ),
	( "sol", "lua - results/lua bench tests sol.csv", "#000000" ),
	( "swig", "lua - results/lua bench tests swig.csv", "#000000" ),
	( "luwra", "lua - results/lua bench tests luwra.csv", "#000000" ),
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
					target.append(v)

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

# Create a blank figure
graph = plt.figure()

# We need one set of bars / graphs / charts for each result, right?
for result in results:
	# subplot that represents this result type
	axes = graph.add_subplot(111)
	axes.set_title(result.name)

	# each category gets its own X spot
	for category in result.samples:
		category_index = crunch_categories.index(category)
		samples = result.samples[category]
		mean = result.means[category]
		stddev = result.stddevs[category]
		meanerror = result.meanerrors[category]
		xvalues = [ ( ( i % 20 ) / 20 ) + category_index * 2 for i in range(0, len(samples))]
		color = result.color

		# Add a point to every axis
		axes.scatter(xvalues, samples, color=color, edgecolor='none')
		# TODO: histogram from the mean of the scatter values
		# meanbar = axes.hist([mean], [1], color='green')
	break

plt.show()
