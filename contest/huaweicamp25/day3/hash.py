import hashlib
import sys
import re

fname = sys.argv[1]
f = open(fname, encoding="utf8")
fout = open(fname + ".hash", "w", encoding="utf8")
for i in f.readlines():
    no_space = "".join(i.split())
    no_comment = no_space.split("//")[0]
    fout.write(f"{hashlib.sha256(no_comment.encode('utf8')).hexdigest()[:4]} |  {i}")
f.close()
fout.close()
