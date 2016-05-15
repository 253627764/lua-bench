import matplotlib.pyplot as plt
import csv


bench_files = [
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests kaguya.csv",
	"lua bench tests luaapipp.csv",
	"lua bench tests luacppinterface.csv",
	"lua bench tests luawrapper.csv",
	"lua bench tests oolua.csv",
	"lua bench tests plain C.csv",
	"lua bench tests selene.csv",
	"lua bench tests slb3.csv",
	"lua bench tests sol.csv",
	"lua bench tests swig.csv",
	"lua bench tests luwra.csv",
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
	
	def __init__(self, name, file):
		self.name = name
		self.file = file
		self.categories = []
		self.process()

	def process(self):
		filehandle = open(self.file)
		rows = csv.DictReader(filehandle)
		for row in rows:
			k = row[0]
			v = row[1]
			k = str(k)
			k = k.split('-')
			
			


plt.plot([1,2,3,4])
plt.ylabel('some numbers')
plt.show()

