===========
vmod_common
===========

-------------------
Varnish Lang Module
-------------------

:Author: Michael Bischof
:Date: 2014-05-09
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import common;

DESCRIPTION
===========

A varnish vmod for common functions (similar to the std vmod).

FUNCTIONS
=========

toupper
-------

Prototype
        ::

		toupper(STRING s, ...)
Return value
	STRING
Description
	Converts the string(s) to upper case.
Example
        ::

		set resp.http.x-test = common.toupper("test");

tolower
-------

Prototype
        ::

		tolower(STRING s, ...)
Return value
	STRING
Description
	Converts the string(s) to lower case.
Example
        ::

		set resp.http.x-test = common.tolower("TEST");

strlen
------

Prototype
        ::

		strlen(STRING s, ...)
Return value
	INT
Description
	Returns the length of the string(s) in bytes.
Example
        ::

		set resp.http.x-test = common.strlen("TEST");

substr
------

Prototype
        ::

		strlen(STRING s, INT start, INT length)
Return value
	INT
Description
	Returns a part of a string starting from start (counting from zero) up to length bytes.
Example
        ::

		set resp.http.x-test = common.substr("HELLO WORLD", 0, 5);

random
------

Prototype
        ::

		random(REAL a, REAL b)
Return value
	REAL
Description
	Returns a random number between a and b.
Example
        ::

		set resp.http.x-test = common.random(1, 99);

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::
	
	import common;

	sub vcl_deliver {
		set resp.http.x-lang = common.toupper(req.http.Accept-Lanugage);
	}

HISTORY
=======

This manual page was released as part of the varnish-vmod-common package.
For further modules and inspiration check the vmod directory:
https://www.varnish-cache.org/vmods

COPYRIGHT
=========

This document is licensed under the same license as the
varnish-vmod-common project. See LICENSE for details.

* Copyright (c) 2014 by Byteworks GmbH

