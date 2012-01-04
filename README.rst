==========================================
 Hinor: autocompletion made easy
==========================================

What is this about?
===================
Hinor is a simple project that uses a specific data structure to store, retrieve and perform autocompletion operations on a set of keys.
Keys are stored in a sort of ternary-(patricia)-trie (i will later describe this data structure in details). Hinor is written in c, is super fast and can easily be used as a python extension.


Features
========

In hinor, you can 
* create the data structure

* add keys to the structure

* associate values to keys

* use the structure as a hash map

* perform an autocompletion lookup: hinor will return a list (json encoded) of keys that begin with a certain string


Hinor as a pythoon extension
============================
To install hinor as a python extension:

cd pytrie
python setup.py build
python setup.py install

optionally:
python tests/test_chartrie.py
python tests/speedtest.py

On my system (i7 2.2 ghz) these are the results:

Adding 100000 keys without values

Medium time:0.300259669622

Adding 100000 keys with values

Medium time:0.321854670842

Getting 100000 keys

Medium time:0.129759788513

Autocomp 100000 keys

Medium time:1.0404056708


Look into the tests code for api documentation.

Notes
===========
Right now, hinor is not suitable for a production environment due to its massive memory usage. I'm working on a compression system for the data structure. Also, some features are still to be tested, and i must document all the api (c and python).


Contributing
============
You are highly encouraged to participate in the development, simply use
GitHub's fork/pull request system.
If you don't like GitHub (for some reason) you're welcome
to send regular patches to the mailing list.
