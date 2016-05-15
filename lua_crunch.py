import matplotlib.pyplot as plt
import csv

bench_targets = [
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
	bench_categories = [
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
		self.categories = []
		self.process()

	def process(self):
		filehandle = open(self.file)
		rows = csv.DictReader(filehandle)
		for row in rows:
			k = row[0]
			v = row[1]
			k = str(k)
			k = k.split(' - ')[1]
			
results = []

for t in bench_targets:
	results.append(benchmark_result(t[0], t[1], t[2]))


plt.plot([1,2,3,4])
plt.ylabel('some numbers')
plt.show()

