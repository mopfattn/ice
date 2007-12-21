#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

import os, sys

for toplevel in [".", "..", "../..", "../../..", "../../../..", "../../../../.."]:
    toplevel = os.path.normpath(toplevel)
    if os.path.exists(os.path.join(toplevel, "config", "TestUtil.py")):
        break
else:
    raise "can't find toplevel directory!"

sys.path.append(os.path.join(toplevel, "config"))
import TestUtil

testdir = os.path.dirname(os.path.abspath(__file__))

ice_home = None
if not os.environ.has_key('ICE_HOME'):
    relPath = os.path.join(TestUtil.findTopLevel(), "cpp", "bin") 
    checkfile = "glacier2router"
    if TestUtil.isWin32():
        checkfile = checkfile + ".exe" 
    if os.path.exists(os.path.join(relPath, checkfile)):
        ice_home = os.path.dirname(relPath) 
    else:
        print "ICE_HOME is not defined."
        sys.exit(0)
else:
    ice_home = os.environ['ICE_HOME']

router = os.path.join(ice_home, "bin", "glacier2router")

args =  r' --Ice.PrintProcessId' \
        r' --Glacier2.RoutingTable.MaxSize=10' + \
        r' --Glacier2.Client.Endpoints="default -p 12347 -t 10000"' + \
        r' --Ice.Admin.Endpoints="tcp -h 127.0.0.1 -p 12348 -t 10000"' + \
        r' --Ice.Admin.InstanceName=Glacier2' + \
        r' --Glacier2.CryptPasswords="' + os.path.join(testdir, "passwords")  + '"'

print "starting router...",
routerConfig = TestUtil.DriverConfig("server")
routerConfig.lang = "cpp"
starterPipe = TestUtil.startServer(router, args + " 2>&1", routerConfig)
TestUtil.getServerPid(starterPipe)
TestUtil.getAdapterReady(starterPipe)
print "ok"

name = os.path.join("Glacier2", "attack")
os.environ["CLASSPATH"] = os.path.join(testdir, "classes") + os.pathsep + os.getenv("CLASSPATH", "")

TestUtil.clientServerTest(name)

if TestUtil.serverStatus():
    sys.exit(1)

sys.exit(0)
