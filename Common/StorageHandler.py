#!/usr/bin/python
### Ahmad Riyadh Al Faathin - 155150207111052 - SKT C - Faathin.com ###
# Import library pydoop
from pydoop import hdfs

class StorageHandler:
    
    hdfsobj=hdfs.hdfs()

    def __init__(self, host, port):
        self.hdfsobj = hdfs.hdfs(host, port, user="vagrant", groups=["vagrant"])

    def pwd(self):
        return self.hdfsobj.working_directory()

    def listDirectory(self, path="/"):
        return self.hdfsobj.list_directory(path)
    
    def delete(self, path):
        self.hdfsobj.delete(path, False)

    def put(self, source, destination):     
        hdfs.put(source, destination)

    def copyFile(self, source, destination):
        self.hdfsobj.copy(source, self.hdfsobj, destination)

    def write(self, path, mod, data):
        with hdfs.open(path, mod) as f:
            f.write(data)