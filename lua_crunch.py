import matplotlib.pyplot as plt
import csv

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
	known_crunch_categories = [
		"global get",
		"global set",
		"table chained get",
		"table get",
		"table chained set",
		"table set",
		"c function",
		"c function through lua",
		"lua function",
		"member function calls",
		"member variable"
	]
	
	def __init__(self, name, file, color):
		self.name = name
		self.file = file
		self.color = color
		self.results = {}
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
					k = str(k)
					splits = k.split(' - ', 1)
					if len(splits) > 1:
						k = splits[1]
					v = float(v)
					# append into right place
					target = None
					if fieldname in self.results:
					    target = self.results[fieldname]
					else:
						target = []
						self.results[fieldname] = target
					target.append(v)

		self.color
			
crunch_categories = []
results = []
for t in crunch_targets:
	results.append(benchmark_result(t[0], t[1], t[2]))


plt.plot([1,2,3,4])
plt.ylabel('some numbers')
plt.show()

