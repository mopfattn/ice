// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <IceGrid/FileUserAccountMapperI.h>

#include <fstream>

using namespace std;
using namespace IceGrid;

FileUserAccountMapperI::FileUserAccountMapperI(const string& filename)
{
    ifstream file(filename.c_str());
    if(!file)
    {
	throw "cannot open `" + filename + "' for reading: " + strerror(errno);
    }
	    
    const string delim = " \t\r\n";
    while(true)
    {
	string line;
	getline(file, line);
	if(!file)
	{
	    break;
	}

	string::size_type idx = line.find('#');
	if(idx != string::npos)
	{
	    line.erase(idx);
	}
		
	idx = line.find_last_not_of(delim);
	if(idx != string::npos && idx + 1 < line.length())
	{
	    line.erase(idx + 1);
	}
    
	string::size_type beg = line.find_first_not_of(delim);
	if(beg == string::npos)
	{
	    continue;
	}

	string::size_type end = line.find_last_of(delim);
	if(end == string::npos || end <= beg)
	{
	    continue;
	}
    
	string user = line.substr(beg, end - beg);
	string account = line.substr(end + 1);

	assert(!user.empty());
	assert(!account.empty());

	_accounts.insert(make_pair(user, account));
    }
}

string
FileUserAccountMapperI::getUserAccount(const string& user, const Ice::Current&)
{
    map<string, string>::const_iterator p = _accounts.find(user);
    if(p == _accounts.end())
    {
	throw UserAccountNotFoundException();
    }
    return p->second;
}
