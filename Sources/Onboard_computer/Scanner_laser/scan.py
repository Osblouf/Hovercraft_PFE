# import the module
from scanner import Scanner

# Load the module
s = Scanner()
s.load_configs()
s.start_module()
# Scan
#while 1:
print str(s.get_plan_distance())
print str(s.get_plan_distance())

# Exit safely (never gets here... Too bad)
exit()
