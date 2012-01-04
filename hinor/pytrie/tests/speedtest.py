from hinor import CharTrie
from timeit import Timer
import hashlib
from random import randint
import time
import gc
REPEAT = 3


def format_res(r):
  return "Medium time:" + str(sum(r)/float(len(r)))

def speed_insert(data,c):
  ct_add = c.add
  for d in data:
    ct_add(d)
    
def speed_insert_val(data,c):
  ct_add = c.add
  for k,v in data:
    ct_add(k,v)
    
def speed_get(data,c):
  ct_get = c.get
  for d in data:
    ct_get(d)

def speed_autocmp(data,c):
  ct_atc = c.autocomp
  for d in data:
    ct_atc(d)

def speedtest():
  
  print "Adding %d keys without values" %len(data_add)
  t = Timer("speed_insert(data_add,c_add)", "from __main__ import speed_insert,data_add,c_add")
  print format_res(t.repeat(REPEAT,number=1))
  
  
  print "Adding %d keys with values" %len(data_add_val)
  t = Timer("speed_insert_val(data_add_val,c_val)", "from __main__ import speed_insert_val,data_add_val,c_val")
  print format_res(t.repeat(REPEAT,number=1))
  
  print "Getting %d keys" %len(data_get)
  t = Timer("speed_get(data_get,c_val)", "from __main__ import speed_get,data_get,c_val")
  print format_res(t.repeat(REPEAT,number=1))
  
  print "Autocomp %d keys" %len(data_autocmp)
  t = Timer("speed_autocmp(data_autocmp,c_val)", "from __main__ import speed_autocmp,data_autocmp,c_val")
  print format_res(t.repeat(REPEAT,number=1))
  
  
  
  
if __name__ == '__main__':
  print "Perparing data"
  data_add = [hashlib.md5(str(i)).hexdigest() * randint(1,5) for i in range(100000)]
  data_add_val = [(data_add[i],hashlib.md5(str(i)).hexdigest() * randint(1,5)) for i in range(100000)]
  data_get = [d for d in data_add[0:80001]]+\
		[d[randint(1,3):randint(4,8)] for d in data_add[80000:-1]]
  data_autocmp = [d[0:randint(3,8)] for d in data_add[0:80001]]+\
      [d[randint(1,3):randint(4,8)] for d in data_add[80000:-1]]
      
  o = open('/tmp/a','w')
  o.write("\n".join([k+":"+v for k,v in data_add_val]))
  c_add = CharTrie()
  c_val = CharTrie()
  #speed_insert_val(data_add_val,c_val)
  #c_val.get("a")
  speedtest()
  
  
