// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestI.h>

ThrowerI::ThrowerI(const Ice::ObjectAdapterPtr& adapter) :
    _adapter(adapter)
{
    _a = APrx::uncheckedCast(_adapter->addTemporary(new A));
    _b = BPrx::uncheckedCast(_adapter->addTemporary(new B));
    _c = CPrx::uncheckedCast(_adapter->addTemporary(new C));
}

void
ThrowerI::shutdown()
{
    _adapter->getCommunicator()->shutdown();
}

void
ThrowerI::throwAasA(Ice::Int a)
{
    APtr p = new A;
    p->a = a;
    p->_throw();
}

void
ThrowerI::throwAasAproxy()
{
    _a->_throw();
}

void
ThrowerI::throwBasA(Ice::Int a, Ice::Int b)
{
    throwBasB(a, b);
}

void
ThrowerI::throwBasAproxy()
{
    throwBasBproxy();
}

void
ThrowerI::throwCasA(Ice::Int a, Ice::Int b, Ice::Int c)
{
    throwCasC(a, b, c);
}

void
ThrowerI::throwCasAproxy()
{
    throwCasCproxy();
}

void
ThrowerI::throwBasB(Ice::Int a, Ice::Int b)
{
    BPtr p = new B;
    p->a = a;
    p->b = b;
    p->_throw();
}

void
ThrowerI::throwBasBproxy()
{
    _b->_throw();
}

void
ThrowerI::throwCasB(Ice::Int a, Ice::Int b, Ice::Int c)
{
    throwCasC(a, b, c);
}

void
ThrowerI::throwCasBproxy()
{
    throwCasCproxy();
}

void
ThrowerI::throwCasC(Ice::Int a, Ice::Int b, Ice::Int c)
{
    CPtr p = new C;
    p->a = a;
    p->b = b;
    p->c = c;
    p->_throw();
}

void
ThrowerI::throwCasCproxy()
{
    _c->_throw();
}
